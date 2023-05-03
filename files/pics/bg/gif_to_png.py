from PIL import Image

with Image.open('files/pics/bg/input.gif') as im:
    for i in range(im.n_frames):
        im.seek(i)
        resized_im = im.resize((1200, 850))
        resized_im.save(f'files/pics/bg/{i}.png')
