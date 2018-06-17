from bs4 import BeautifulSoup
import os


def get_html_content(path):
    with open(path,"r") as f:
        soup = BeautifulSoup(f,'lxml')
        print (soup.title)
        print (soup.head)
        print (dir(soup))

        # content = soup.text.strip('\n')
        # print (content)
def get_html_href(path):
    with open(path,'r') as f:
        soup = BeautifulSoup(f,'lxml')
        for a in soup.find_all('a'):
            print (a.attrs['href'])
            print (a.get('href'))
        for href in soup.find_all("href"):
            print (href)
def main():
    get_html_href('html_test.html')


if __name__ == '__main__':
    main()
