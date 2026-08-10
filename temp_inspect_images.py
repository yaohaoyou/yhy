from PIL import Image
for i in range(31, 38):
    path = f'English/{i}.png'
    im = Image.open(path)
    w, h = im.size
    print(i, w, h, im.mode)
    crop = im.crop((0, 0, w, h // 6))
    crop.save(f'temp_{i}_top.png')
print('done')
