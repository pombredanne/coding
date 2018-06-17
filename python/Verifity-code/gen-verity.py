# coding=utf-8
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import random
import string
import functools
import logging

logging.basicConfig(level=logging.INFO)

IMAGE_MOOD = 'RGB'
IMAGE_BG_COLOR = (255, 255, 255)
Image_Font = 'Ubuntu-B.ttf'
text = "".join(random.sample(string.ascii_letters, 4))


def log(text):
    def decorator(func):
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)

        return wrapper

    return decorator


def color_random():
    return (random.randint(0, 255), random.randint(0, 255), random.randint(0, 25))


@log('exec')
def create_verity_code(text, width=400, height=200, chance=2):
    im = Image.new(IMAGE_MOOD, (width, height), IMAGE_BG_COLOR)
    draw = ImageDraw.Draw(im)
    for w in range(width):
        for h in range(height):
            if chance < random.randint(1, 100):
                draw.point((w, h), fill=color_random())
    font = ImageFont.truetype(Image_Font, 80)
    font_width, font_height = font.getsize(text)
    text_len = len(text)
    x = (width - font_width) / 2
    y = (height - font_height) / 2
    for i in text:
        draw.text((x, y), i, color_random(), font)
        x += font_width / text_len
    im.filter(ImageFilter.BLUR)
    im.save("verity_code.png")


if __name__ == '__main__':
    create_verity_code(text)
