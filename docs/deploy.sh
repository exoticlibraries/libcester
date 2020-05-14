
mkdir -p dist/gh-pages/
cd dist/gh-pages/
git clone -b gh-pages https://github.com/exoticlibraries/libcester.git
cd libcester/
cp -r ../../../docs/build/html/* ./
ls
git config --local user.email "azeezadewale98@gmail.com"
git config --local user.name "travis-ci.org"
git add .; git commit -m "Travis build=${TRAVIS_BUILD_NUMBER}. Update Documentation from Travis CI"
git push -f https://Thecarisma:${GITHUB_TOKEN}@github.com/exoticlibraries/libcester.git HEAD:gh-pages;
cd ../../../
