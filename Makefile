all:
	g++ -std=c++14 $(f).cpp -o $(f) -O2 -Wall -Wextra -Wshadow -Wno-unused-result -Wno-sign-compare -fsanitize=undefined -fno-sanitize-recover