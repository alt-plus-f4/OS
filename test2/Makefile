all: stock_market.c tickets_chaos.c
	gcc stock_market.c -o stock -pthread
	gcc tickets_chaos.c -o tickets -pthread

stock: stock_market.c
	gcc stock_market.c -o stock -pthread
tickets: tickets_chaos.c
	gcc tickets_chaos.c -o tickets -pthread

test_stock: stock
	./stock 50 50

test_tickets: tickets
	./tickets 10000

