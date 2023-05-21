import cv2

capture = cv2.VideoCapture("http://192.168.1.5:8080/video")



while(True):
    _,frame = capture.read()
    
    cv2.imshow('livestream',frame)
    
    if cv2.waitKey(1) == ord("q"):
        break

capture.release()
cv2.destroyAllWindows()