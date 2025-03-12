from PIL import Image, ImageDraw
import os
import cv2
file = open("file_insert.txt", "r")
arr = file.readlines()

high = 1080
width = 1920

number_of_elem = len(arr[0].split())
Col_size = (width-100)/number_of_elem

Col_high_max = 0

for elem in arr[0][:-1].split():
    if Col_high_max < int(elem):
        Col_high_max = int(elem)



for i in range(len(arr)):
    new_img = Image.new('RGB', (width, high), 'black')
    pencil = ImageDraw.Draw(new_img)
    content = arr[i].split()
    for j in range(len(content)):
        pencil.rectangle((Col_size * j, high - int(content[j])/Col_high_max * (high-50), Col_size * j + Col_size, high), fill='green')

    name = "Images/Image_" + "0"*(6- len(str(i)) ) + str(i) +  ".jpg"
    new_img.save(name)

def generate_video():
    image_folder = "Images"
    video_name = 'mygeneratedvideo.avi'

    images = [img for img in os.listdir(image_folder) if img.endswith((".jpg", ".jpeg", ".png"))]

    print("Images:", images)

    # Set frame from the first image
    frame = cv2.imread(os.path.join(image_folder, images[0]))
    height, width, layers = frame.shape

    # Video writer to create .avi file
    video = cv2.VideoWriter(video_name, cv2.VideoWriter_fourcc(*'DIVX'), 100, (width, height))

    # Appending images to video
    for image in images:
        video.write(cv2.imread(os.path.join(image_folder, image)))

    # Release the video file
    video.release()
    cv2.destroyAllWindows()
    print("Video generated successfully!")

generate_video()
for i in range(len(arr)):
    name = "Images/Image_" + "0" * (6 - len(str(i))) + str(i) + ".jpg"
    os.remove(name)