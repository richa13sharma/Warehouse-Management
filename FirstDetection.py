from imageai.Detection import ObjectDetection
import os
import numpy as np
import cv2

execution_path = os.getcwd()

detector = ObjectDetection()
detector.setModelTypeAsRetinaNet()
detector.setModelPath( os.path.join(execution_path , "resnet50_coco_best_v2.0.1.h5"))
detector.loadModel()
video = cv2.VideoCapture(0)
ret = video.set(3,1280)
ret = video.set(4,720)
success = 1

while(success):

    # Acquire frame and expand frame dimensions to have shape: [1, None, None, 3]
    # i.e. a single-column array, where each item in the column has the pixel RGB value
    ret, frame = video.read()
    frame_expanded = np.expand_dims(frame, axis=0)
    success, image = video.read() 
  
    # Saves the frames with frame-count 
    cv2.imwrite("frame.jpg", image) 
    detections = detector.detectObjectsFromImage(input_image=os.path.join(execution_path , "frame.jpg"), output_image_path=os.path.join(execution_path , "imagenew.jpg"))
    # detections = detector.detectObjectsFromImage(input_image=frame, output_image_path=os.path.join(execution_path , "imagenew.jpg"))
    # cv2.imshow('Object detector', frame)
    # print(detections)
    for eachObject in detections:
        if(eachObject["name"] == 'person' and eachObject["percentage_probability"] >= 90):
            print("Turn buzzer on")
            video.release()
            exit(0)
        # print(eachObject["name"] , " : " , eachObject["percentage_probability"] )
        # if cv2.waitKey(1) == ord('q'):
        #     video.release()
        #     break
        
    # Press 'q' to quit
    
    
    
