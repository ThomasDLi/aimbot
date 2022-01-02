import cv2
import requests
import time
cascPath = "fd.xml"
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.CASCADE_SCALE_IMAGE
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        
        halfx = int(x + (w/2))
        halfy = int(y + (h/2))

        #width and height of video
        camw = int(video_capture.get(3))
        camh = int(video_capture.get(4))

        cv2.rectangle(frame, (halfx, halfy), (halfx+1, halfy+1), (0, 255, 0), 2)
        cv2.rectangle(frame, (int(camw / 2) - 50, int(camh / 2) - 50), (int(camw / 2) + 50, int(camh / 2) + 50), (0, 255, 0), 2)

        #angle camera

        if(halfx < int(camw / 2) - 50):
            print("left")
            requests.get("http://192.168.4.1/left")

        elif(halfx > int(camw / 2) + 50):
            print("right")

        elif(halfy < int(camh / 2) - 50):
            print("up")

        elif(halfy > int(camh / 2) + 50):
            print("down")

        else:
            print("shoot")

    # Display the resulting frame
    cv2.imshow('Video', frame)
    time.sleep(0.05)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
