from bs4 import BeautifulSoup
import re
from urllib import request
import functools
import logging
import os

logging.basicConfig(level=logging.INFO)


def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)

    return wrapper


@log
def get_blog_urls(pages):
    blog_urls = []
    for page in pages:
        content = request.urlopen(page)
        soup = BeautifulSoup(content, 'lxml')
        div_list = (soup.find_all('h4', {'class': 'text-truncate'}))
        for div in div_list:
            url = div.a['href']
            blog_urls.append(url)
    return blog_urls


@log
def get_blog2md(url):
    content = request.urlopen(url)
    soup = BeautifulSoup(content, 'lxml')
    blog_name = soup.find('h1', {'class': 'title-article'}).get_text()
    blog_name = re.sub(r'/', '-', blog_name)
    file_name = os.path.join('./MyBlog', blog_name + '.html')
    blog_content = soup.find('div', {"class": "blog-content-box"}).prettify()  # get html
    with open(file_name, 'w') as f:
        f.write(blog_content)
        f.flush()
    logging.info("%s write done!" % (file_name))


@log
def get_pages(myblog):
    page_list = []
    for i in range(1, 10):
        myblog_ = myblog + str(i) + '?t=1'
        content = request.urlopen(myblog_)
        soup = BeautifulSoup(content, 'lxml')
        _not_page = (
            soup.find('div', {'class': 'no-data d-flex flex-column justify-content-center align-items-center'}))
        if _not_page is not None:
            break
        else:
            page_list.append(myblog_)
    return page_list


def main(myblog):
    pages = get_pages(myblog)
    urls = get_blog_urls(pages)
    for url in urls:
        get_blog2md(url)
        # print(url)


def test():
    a = 0
    c = []
    for a in range(-1, 4):
        print(a)
        try:
            b = 2 / a
        except Exception as e:
            print("exception:", e)
            continue
        c.append(b)
    print(c)


def testlog():
    logging.info("Done!")


def test_filename():
    filename = './MyBlog/' + '123/3.txt'
    file = re.sub(r'/', '', filename)
    print(file)


if __name__ == '__main__':
    # test()
    # testlog()
    # test_filename()
    # content = request.urlopen("https://blog.csdn.net/qq_33438733/article/details/79254908")
    # get_blog2md(content)
    myblog = 'https://blog.csdn.net/qq_33438733/article/list/'
    main(myblog)
