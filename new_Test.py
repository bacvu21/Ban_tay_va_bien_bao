import numpy as np # thư viện số học dungf để tính toán xử lí ảnh 
import cv2
import time 

net = cv2.dnn.readNet('yolov4_training_last.weights', 'yolov4_testing.cfg') # đọc dữ lieeuyj đã training 

classes = []
with open("classes.txt", "r") as f:
    classes = f.read().splitlines()

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_PLAIN
starting_time = time.time()
frame_id = 0 

while True:
    ret, frame = cap.read() #đọc từng frame 1 
    frame_id += 1
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
            confidence = str(round(confidences[i], 2))
            color = colors[i]
            cv2.rectangle(frame, (x, y), (x + w, y + h), color, 3)
            cv2.putText(frame, label + " " + confidence, (x, y + 20), font, 2, (255, 0, 0), 2)

    elapsed_time = time.time() - starting_time
    fps = frame_id/elapsed_time
    cv2.putText(frame, "FPS: " + str(round(fps, 2)), (10, 50), font, 4, (0, 0, 0), 3)
    cv2.imshow("Real Time", frame)

    key1 = cv2.waitKey(1)
    if key1 == 27:
        break

cap.release()
cv2.destroyAllWindows()
