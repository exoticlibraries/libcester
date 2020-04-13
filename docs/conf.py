import themata

project = 'libcester'
copyright = '2020, Adewale Azeez, Creative Commons Zero v1.0 Universal License'
author = 'Adewale Azeez'

html_theme_path = [themata.get_html_theme_path()]
html_theme = 'milkish'
html_favicon = 'libcester.png'

html_theme_options = {
    'index_is_single': False,
    'show_navigators_in_index': False,
    'collapsible_sidebar': True,
    'collapsible_sidebar_display': 'block',
    'navbar_links': [
        ('Download', './download.html'),
        ('Documentation', './docs/'),
        ('Contribute on Github', 'https://github.com/Thecarisma/themata/')
    ],
    'has_left_sidebar': True,
    'has_right_sidebar': True,
    'show_navigators': True,
    'social_icons': [
        ('fab fa-twitter', 'https://twitter.com/iamthecarisma'),
        ('fab fa-github', 'https://github.com/exoticlibraries/libcester/')
    ],
    'no_sidebar': [
        'index'
    ],
    # the styles
    "header_background_color": "black"
}