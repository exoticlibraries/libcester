
rm -R build/
sphinx-build -b html -d build/doctrees  ./ build/html
doxygen
touch ./build/html/.nojekyll