coverage run -m unittest discover -s tests -p "test_*.py" -v
coverage report -m 
rm .coverage