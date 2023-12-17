import cv2
import os
import time
import Hand_tracking_module as htm
import serial

def getNumber(ar):
    s = ""
    for i in ar:
        s += str(ar[i])

    # Mapping finger patterns to numbers
    if s == "00000":
        return 0
    elif s == "01000":
        return 1
    elif s == "01100":
        return 2 
    elif s == "01110":
        return 3
    elif s == "01111":
        return 4
    elif s == "11111":
        return 5 
    elif s == "01001":
        return 6
    elif s == "01011":
        return 7

# Webcam setup
wcam, hcam = 640, 480
cap = cv2.VideoCapture(0)
cap.set(3, wcam)
cap.set(4, hcam)

pTime = 0
detector = htm.handDetector(detectionCon=0.75)

# Initialize the serial connection
ser = serial.Serial("COM11", 9600, timeout=1)

while True:
    success, img = cap.read()
    img = detector.findHands(img, draw=True)
    lmList = detector.findPosition(img, draw=False)

    tipId = [4, 8, 12, 16, 20]
    
    if len(lmList) != 0:
        fingers = []

        # Thumb
        if lmList[tipId[0]][1] > lmList[tipId[0] - 1][1]:
            fingers.append(1)
        else:
            fingers.append(0)

        # 4 fingers
        for id in range(1, len(tipId)):
            if lmList[tipId[id]][2] < lmList[tipId[id] - 2][2]:
                fingers.append(1)
            else:
                fingers.append(0)

        # Display finger count on the frame
        cv2.rectangle(img, (20, 255), (170, 425), (0, 255, 0), cv2.FILLED)
        finger_count = getNumber(fingers)
        cv2.putText(img, str(finger_count), (45, 375), cv2.FONT_HERSHEY_PLAIN, 10, (255, 0, 0), 20)

        # Send messages to ESP8266 based on finger count
        if finger_count in range(1, 7):
            ser.write(bytes([0x60 + finger_count]))  # Sending 'a' to 'g'

    # Frame processing and display
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
    cv2.putText(img, f'FPS: {int(fps)}', (400, 70), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 0), 3)
    cv2.imshow("image", img)
    
    # Exit loop when 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Close the serial connection and release the camera
ser.close()
cap.release()
cv2.destroyAllWindows()
