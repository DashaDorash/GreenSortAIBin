import cv2  # Import OpenCV library
from inference_sdk import InferenceHTTPClient
import time
import serial
API_KEY = "hvnVuPnZRTpEFQn9TWKn"

def classify_waste(image_path):
    CLIENT = InferenceHTTPClient(
        api_url="https://detect.roboflow.com",
        api_key=API_KEY
    )

    result = CLIENT.infer(image_path, model_id="yolo-waste-detection/1")
    return result  # Returns classification result


RECYCLABLE_CLASSES = {
    "Cardboard", "Paper", "Paper bag", "Paper cups", "Paper shavings", "Papier mache", "Printing industry",
    "Aluminum can", "Aluminum caps", "Foil", "Scrap metal", "Iron utensils", "Metal shavings",
    "Glass bottle",
    "Plastic bottle", "Plastic caps", "Plastic cup", "Plastic can", "Plastic canister", "Plastic shaker", "Plastic bag",
    "Combined plastic",
    "Electronics"
}


def is_recyclable(image_path, max_retries=3):
    # retry_count = 0
    # while retry_count < max_retries:
    # Run classification
    result = classify_waste(image_path)

    if "predictions" in result and len(result["predictions"]) > 0:
        waste_class = result["predictions"][0]["class"]
        if waste_class in RECYCLABLE_CLASSES: # Define recyclable items
            print(f"That's {waste_class}. Throw it in")
            return 'O'  # Return command open if recyclable
        else:
            print(f"That's {waste_class}! Cant recycle. Wrong Bin")
            return 'F'

    # If no object detected, send "Try Again" message to Arduino
    print("No object detected. Asking user to try again...")
    return "R"  # Custom message to Arduino

    # **Recapture Image**
    # new_image_path = image_capture.capture_image()  # Take a new photo
    # image_path = new_image_path  # Update image path for next iteration
    # retry_count += 1

    # print("Max retries reached. Cannot detect object.")
    # arduino.write(b"False\n")
    # print("False")
    return False  # Assume non-recyclable if still undetected


def capture_image(output_path="captured_image.jpg"):
    cap = cv2.VideoCapture(0)  # Open the default webcam (0)
    time.sleep(2)
    
    if not cap.isOpened():
        print("Error: Could not open webcam.")
        return None

    ret, frame = cap.read()  # Capture a single frame

    if ret:  # If the frame was captured successfully
        cv2.imwrite(output_path, frame)  # Save the image
        print(f"Image saved at {output_path}")
    else:
        print("Error: Could not capture image.")

    cap.release()  # Release the webcam

    return is_recyclable(output_path)  # Return the path of the saved image


def main():
    arduino = serial.Serial(port='/dev/cu.usbmodem101', baudrate=9600, timeout=.1)
    time.sleep(5)
    print("port initialized")
    while True:
        if arduino.in_waiting > 0:
            # Read line from Arduino
            line = arduino.readline().decode('utf-8').strip()
            print(f"Arduino says: {line}")

            if line == "P":
                # 1. Capture image from webcam
                arduino.write((capture_image() + "\n").encode())




main()