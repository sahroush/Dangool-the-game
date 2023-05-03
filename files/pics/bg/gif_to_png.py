from PIL import Image
import os

path = 'files/pics/bg/'

if(len(os.listdir(path)) != 2):
	exit(0)

with Image.open(path + 'input.gif') as im:
    for i in range(im.n_frames):
        im.seek(i)
        resized_im = im.resize((1200, 850))
        resized_im.save(path + f'{i}.png')
