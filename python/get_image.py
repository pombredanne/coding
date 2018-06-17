from bs4 import BeautifulSoup
import re
import os
from urllib import request, parse


def download_pic(src):
    image_content = request.urlopen(src).read()
    file_name = parse.urlsplit(src)[2]
    # real_name = re.findall(r'sign=[\w\W\d\D]+',file_name)[0]
    real_name = (os.path.basename(file_name))
    save_name = os.path.join('./image', real_name)
    print (save_name)
    output = open(save_name, "wb")
    output.write(image_content)
    output.close()


def main(url):
    with request.urlopen(url) as f:
        soup = BeautifulSoup(f, "lxml")
        for i in soup.find_all("img", {"class": 'BDE_Image'}):
            src = i.get('src')
            download_pic(src)


if __name__ == '__main__':
    main("http://tieba.baidu.com/p/2166231880?traceid=")
