import themata

project = 'libcester'
copyright = '2020, Adewale Azeez, GNU GPLv3'
author = 'Adewale Azeez'

html_theme_path = [themata.get_html_theme_path()]
html_theme = 'milkish'
html_favicon = 'libcester.png'
master_doc = 'index'
html_static_path = ['_static']
html_context = {
    'css_files': ['_static/css/libcester.css'],
}

html_theme_options = {
    'index_is_single': False,
    'show_navigators_in_index': False,
    'collapsible_sidebar': False,
    'collapsible_sidebar_display': 'block',
    'navbar_links': [
        ('Docs', '/libcester/docs/'),
        ('Reference', '/libcester/reference/'),
        ('Contribute on Github', 'https://github.com/exoticlibraries/libcester/'),
        ('Exotic Libraries', 'https://exoticlibraries.github.io/')
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
    "source_root": "https://github.com/exoticlibraries/libcester/edit/master/docs",
    "document_font_size": "17px",
    "text_color": "rgb(205,202,194)",
    "link_color": "rgb(205,202,194)",
    "highlight_color": "rgb(15,110,157)",
    "header_background_color": "rgb(52,55,58)",
    "background_color": "rgb(24,26,27)",
    "pre_background_color": "rgb(24,26,27)",
    "pre_border_color": "rgb(84,91,98)"
}