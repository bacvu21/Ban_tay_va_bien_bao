import cv2 
import time 
import os 
import numpy as np
import Hand_tracking_module as htm 
import serial 
wCam,hCam = 640,480

# Initialize the serial connection
ser = serial.Serial('COM4', 9600,timeout=1)


net = cv2.dnn.readNet('yolov4_training_last.weights', 'yolov4_testing.cfg')

classes = []
with open("classes.txt", "r") as f:
    classes = f.read().splitlines()

cap = cv2.VideoCapture(0)

cap.set(3,wCam)
cap.set(4,hCam)


folderPath = "image"

myList = os.listdir(folderPath)
print (myList)

overlayList = []

for imPath in myList:
    image = cv2.imread(f'{folderPath}/{imPath}')
    #print (f'{folderPath}/{imPath}')
    overlayList.append(cv2.resize(image, (200, 200)))
    
print(len(overlayList))


pTime = 0


ret = True

detector = htm.handDetector(detectionCon=0.75)

tipIds = [4,8,12,16,20]

font = cv2.FONT_HERSHEY_PLAIN

def process_ (frame):
    height, width, _ = frame.shape
    blob = cv2.dnn.blobFromImage(frame, 1/255, (320, 320), (0, 0, 0), True, crop=False)

    net.setInput(blob)
    output_layers_names = net.getUnconnectedOutLayersNames()
    layerOutputs = net.forward(output_layers_names)

    boxes = []
    confidences = []
    class_ids = []

    for output in layerOutputs:
        for detection in output:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.8:
                center_x = int(detection[0]*width)
                center_y = int(detection[1]*height)
                w = int(detection[2]*width)
                h = int(detection[3]*height)

                x = int(center_x - w/2)
                y = int(center_y - h/2)

                boxes.append([x, y, w, h])
                confidences.append((float(confidence)))
                class_ids.append(class_id)

    number_obj = len((boxes))
    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.8, 0.4)
    colors = np.random.uniform(0, 255, size=(len(boxes), 3))

    for i in range(number_obj):
        if i in indexes:
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            
            if label == "re trai":
                
                
                char_data = chr(97)# is ASCII code of 'a'
                ser.write(char_data.encode())
               
                
                
            confidence = str(round(confidences[i], 2))
            color = colors[i]
            cv2.rectangle(frame, (x, y), (x + w, y + h), color, 3)
            cv2.putText(frame, label + " " + confidence, (x, y + 20), font, 2, (255, 0, 0), 2)



while True:
    ret,img =cap.read()
    img = cv2.resize(img,(640,480))
    process_(img)
    img = detector.findHands(img)
    lmList = detector.findPosition(img,draw=False)
    
    if len(lmList) != 0:
        fingers = []
        #Thumb
    
        if (lmList[tipIds[0]][1] < lmList[tipIds[0]-1][1]): #toa do array 2 
            fingers.append(1)
        else:
            fingers.append(0)
        #4fingers       
        for id in range (1,5):
            if (lmList[tipIds[id]][2] <lmList[tipIds[id]-2][2]): #toa do array 2 
                fingers.append(1)
            else:
                fingers.append(0)
        
        #print(fingers)
        totalFingers = fingers.count(1)
        print(totalFingers)
        
        if totalFingers == 1:
            char_data = chr(97)# is ASCII code of 'a'
            ser.write(char_data.encode())
        elif totalFingers == 2:
            char_data = chr(98)# is ASCII code of 'a'
            ser.write(char_data.encode())
        elif totalFingers == 5:
            char_data = chr(99)# is ASCII code of 'a'
            ser.write(char_data.encode())
        elif totalFingers == 3:
            char_data = chr(100)# is ASCII code of 'a'
            ser.write(char_data.encode())
        elif totalFingers == 4:
            char_data = chr(101)# is ASCII code of 'a'
            ser.write(char_data.encode())
                
        
        
        h,w,c=overlayList[0].shape
        img[0:h, 0:w] = overlayList[totalFingers-1]
        
        
        
        cv2.putText(img , str(totalFingers),(30,450),cv2.FONT_HERSHEY_PLAIN,18,(255,0,0),25)
        
    
    
    
    
    cTime = time.time()
    fps  = 1/(cTime-pTime)
    pTime = cTime 
    cv2.putText(img,f'fps:{int(fps)}',(400,70),cv2.FONT_HERSHEY_PLAIN,3,(255,0,0),3)
    
    
    
    cv2.imshow("image",img)
    
    if cv2.waitKey(1) == ord("q"):
        break
    
    
cap.release()
cv2.destroyAllWindows()