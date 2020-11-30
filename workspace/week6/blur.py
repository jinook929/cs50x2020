from PIL import Image, ImageFilter

before = Image.open("DOG.jpg")
after = before.filter(ImageFilter.BLUR)
after.save("out.jpg")