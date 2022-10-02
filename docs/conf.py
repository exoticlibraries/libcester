import themata.milkish

project = 'libcester'
copyright = '2021, Exotic Libraries - MIT License'
author = 'Adewale Azeez and Other Contributors'

html_theme = 'milkish'
master_doc = 'index'
html_favicon = 'libcester.png'
main_doc = 'index'
html_static_path = ['_static']

html_css_files = {
    'css/libcester.css'
}

html_theme_options = {
    'index_is_single': False,
    'show_navigators_in_index': False,
    'collapsible_sidebar': False,
    'collapsible_sidebar_display': 'block',
    'navbar_links': [
        ('Doc', 'docs/index'),
        ('Reference', 'reference/index'),
        ('Contribute', 'https://github.com/exoticlibraries/libcester/'),
        ('Exotic Libraries', 'https://exoticlibraries.github.io/'),
        ('Support', 'https://exoticlibraries.github.io/pages/support.html')
    ],
    'has_left_sidebar': True,
    'has_right_sidebar': True,
    'show_navigators': True,
    'social_icons': [
        ('fab fa-twitter', 'https://twitter.com/exoticlibs'),
        ('fab fa-github', 'https://github.com/exoticlibraries/libcester/')
    ],
    'no_sidebar': [
        'index'
    ],
    "source_root": "https://github.com/exoticlibraries/libcester/edit/main/docs",
    "document_font_size": "17px",
    "metadata": {
        "enable": True,
        "url": "https://exoticlibraries.github.io/libcester/",
        "type": "website",
        "title": "A robust header only unit testing framework for C programming language.",
        "description": "libcester is a header only automated testing framework for the C programming language, it requires no dependency and can be downloaded and used in a project immediately.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libcester/main/docs/libcester.png",
        "keywords": "thecarisma, c, cpp, c++, unit testing, framework, exoticlibraries, exotic, libraries, regression, test",
        "author": "Adewale Azeez"
    },
    "twitter_metadata": {
        "enable": True,
        "card": "summary",
        "site": "@exoticlibs",
        "creator": "@iamthecarisma",
        "title": "A robust header only unit testing framework for C programming language.",
        "description": "libcester is a header only automated testing framework for the C programming language, it requires no dependency and can be downloaded and used in a project immediately.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libcester/main/docs/libcester.png",
    }
}