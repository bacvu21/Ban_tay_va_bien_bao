import numpy as np
import cv2
import serial
import time
import urllib.request
net = cv2.dnn.readNet('yolov4_training_last.weights', 'yolov4_testing.cfg')

classes = []
with open("classes.txt", "r") as f:
    classes = f.read().splitlines()

#url='http://192.168.1.27:8080/shot.jpg'
#arduino = serial.Serial('COM9', 115200)

#cap = cv2.VideoCapture(url)
font = cv2.FONT_HERSHEY_PLAIN
starting_time = time.time()
frame_id = 0 
#img = cv2.imread('test3.jpg')
while True:
    # imgResp = urllib.request.urlopen(url)
    
    
    # imgNp = np.array(bytearray(imgResp.read()),dtype=np.uint8)
    
    # frame = cv2.imdecode(imgNp,-1)

    frame_id += 1
    height, width, _ = frame.shape

    blob = cv2.dnn.blobFromImage(frame, 1/255, (320, 320), (0, 0, 0), True, crop=False)
    """for b in blob:
        for n, img_blob in enumerate(b): 
            cv2.imshow(str(n), img_blob)
    """
    net.setInput(blob)
    output_layers_names = net.getUnconnectedOutLayersNames()
    layerOutputs = net.forward(output_layers_names)

    boxes = []
    confidences = []
    class_ids = []
    value = arduino.read_all()
    if value == b'1':
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
        #print(len(boxes))
        indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.8, 0.4)
        #print(indexes.flatten())
        colors = np.random.uniform(0, 255, size=(len(boxes), 3))

        for i in range(number_obj):
            if i in indexes:
                x, y, w, h = boxes[i]
                label = str(classes[class_ids[i]])
                confidence = str(round(confidences[i], 2))
                color = colors[i]
                cv2.rectangle(frame, (x, y), (x + w, y + h), color, 3)
                cv2.putText(frame, label + " " + confidence, (x, y + 20), font, 2, (255, 0, 0), 2)

                if class_ids[i] == 0:
                    print("Re Trai")
                    arduino.write(b'1')
                    time.sleep(2)
                elif class_ids[i] == 1:
                    print("Re Phai")
                    arduino.write(b'2')
                    time.sleep(2)
                elif class_ids[i] == 2:
                    print("Quay Dau")
                    arduino.write(b'3')
                    time.sleep(2)
                elif class_ids[i] == 3:
	                print("Tang Toc")
	                arduino.write(b'4')
	                time.sleep(2)
                elif class_ids[i] == 4:
                    print("Giam Toc")
                    arduino.write(b'5')
                    time.sleep(2)
                elif class_ids[i] == 5:
                    print("Dung Lai")
                    arduino.write(b'6')
                    time.sleep(2)
        
        '''if number_obj == 0:
            print("Vat Can")
            arduino.write(b'8')
            time.sleep(2)
            continue'''
        
    key1 = cv2.waitKey(1)
    if key1 == 27:
        break
    elif key1 == 32:
        print("Stop")
        arduino.write(b'st')
    elif key1 == 13:
        arduino.write(b'9')
    elapsed_time = time.time() - starting_time
    fps = frame_id/elapsed_time
    cv2.putText(frame, "FPS: " + str(round(fps, 2)), (10, 50), font, 4, (0, 0, 0), 3)
    cv2.imshow("Real Time", frame)


# do a bit of cleanup
cap.release()
cv2.destroyAllWindows()