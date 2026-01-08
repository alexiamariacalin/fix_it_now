all:
	clear
	@g++ *.cpp
	@./a.out
	@rm a.out
test:
	clear
	@g++ tests/test.cpp
	@./a.out
	@rm a.out
good:
	clear
	@g++ *.cpp
	@./a.out tests/good_appliances.csv tests/good_employees.csv tests/good_requests.csv
	@rm a.out
bad:
	clear
	@g++ *.cpp
	@./a.out tests/bad_appliances.csv tests/bad_employees.csv tests/bad_requests.csv
	@rm a.out
zip:
	zip -r ../fixitnow ../fix_it_now