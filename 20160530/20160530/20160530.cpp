#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "127.0.0.1";
const char* user = "root";
const char* pw = "20160530";
const char* db = "20160530";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	MYSQL_RES* sql_result2;
	MYSQL_ROW sql_row2;

	struct tm* t;
	time_t base = time(NULL);
	t = localtime(&base);

	char* buffer = NULL;
	int size;
	int flag = 1, select = 0, k;
	int new_order = 10000100;
	int new_shipment = 30100;
	char year[10];

	FILE* fp = fopen("20160530.txt", "r");

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	buffer = (char*)malloc(size + 1);
	memset(buffer, 0, size + 1);
	fseek(fp, 0, SEEK_SET);
	fread(buffer, size, 1, fp);

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		int state = 0;
		printf("\n** Create table and insert tuple **\n");
		const char* create = strtok(buffer, ";");
		while (create != NULL) {
			state = 0;
			state = mysql_query(connection, create);
			create = strtok(NULL, ";");
		}
		printf("Completed to create table ans insert tuple\n");

		char query[2024];
		char* customer_ID = nullptr;
		int type, subtype;
		while (flag) {

			printf("\n\n------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf("----------------------------------\n");
			printf("Select Number : ");
			scanf(" %d", &type);
			getchar();
			switch (type) {
			case 0:
				flag = 0;
				break;
			case 1:
				printf("\n\n");
				printf("---- TYPE 1 ----\n\n");
				printf("** Tracking number X is reported to have been destroyed in an accident. **\n");
				
				char Tnum[10];
				printf("Enter Tracking number X : ");
				scanf("%s", Tnum);
				if (Tnum[0] == '0') break;
				

				memset(query, 0, sizeof(query));
				sprintf(query, "select customer_ID, customer_name, contract from customer where customer_ID = (select customer_Id from order_info natural join shipment where shipment_Id = '%s')",Tnum);
				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("Customer : %s, Name : %s, Contact : %s\n", sql_row[0], sql_row[1], sql_row[2]);
						customer_ID = sql_row[0];
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");

				printf("---- Subtypes in TYPE 1 ----\n");
				printf("\t1. TYPE 1-1\n");
				printf("\t0. QUIT\n");
				printf("----------------------------\n");
				printf("Select Number : ");
				scanf(" %d", &subtype);
				if (subtype != 1) break;

				printf("\n---- TYPE 1-1 ----\n\n");
				printf("** Create a new shipment of replacement items. **\n");

				memset(query, 0, sizeof(query));
				sprintf(query, "select product_ID, quantity from comprise where order_ID = (select order_ID from order_info natural join shipment where shipment_Id = '%s')", Tnum);
				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{	
					sql_result = mysql_store_result(connection);
					printf("Shipment_ID : %d, order_ID : %d", new_shipment, new_order);
					memset(query, 0, sizeof(query));
					sprintf(query, "insert into order_info values ('%d', '%s', '%d-%d-%d');", new_order, customer_ID, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
					state = 0;
					state = mysql_query(connection, query);

					memset(query, 0, sizeof(query));
					sprintf(query, "insert into shipment values ('%d', '%d', 'shipment1', '%d-%d-%d', null);", new_shipment++, new_order, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
					state = 0;
					state = mysql_query(connection, query);

					printf("\nProduct_ID Quantity\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s        %-5s\n", sql_row[0], sql_row[1]);
						memset(query, 0, sizeof(query));
						sprintf(query, "insert into comprise values ('%d', '%s', '%s');", new_order, sql_row[0], sql_row[1]);
						state = 0;
						state = mysql_query(connection, query);
					}

					mysql_free_result(sql_result);
				}
				printf("\n\n");

				new_order++;
				printf("** Completed to create a new shipment. **\n\n");
				break;
				
			case 2:
				printf("\n\n");
				printf("---- TYPE 2 ----\n\n");
				printf("** Find the customer who has bought the most (by price) in the past year. **\n");

				char c_ID[10];
				printf("Enter year : ");
				scanf("%s", year);
				if (year[0] == '0') break;

				memset(query, 0, sizeof(query));
				sprintf(query, "with tb as(select customer_ID, sum(quantity*product_price) as total_price from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and  '%s-12-31' group by customer_ID order by total_price desc limit 1) select customer_ID, customer_name, total_price from tb natural join customer;",year,year);
				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("CustomerID : %s, Name : %s, Total amount : %s\n", sql_row[0], sql_row[1], sql_row[2]);
						sprintf(c_ID, sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
				printf("---- Subtypes in TYPE 2 ----\n");
				printf("\t1. TYPE 2-1\n");
				printf("\t0. QUIT\n");
				printf("----------------------------\n");
				printf("Select Number : ");
				scanf(" %d", &subtype);
				if (subtype != 1) break;

				printf("\n---- TYPE 2-1 ----\n\n");
				printf("** Then find the product that the customer bought the most. **\n");
				memset(query, 0, sizeof(query));
				sprintf(query, "select product_ID, product_name, quantity*product_price as total_price from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' and customer_ID = '%s' group by product_ID order by total_price desc limit 1",year,year,c_ID);
				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("Product ID: %s, Name : %s, Total amount : %s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
				break;

			case 3:
				printf("\n\n");
				printf("---- TYPE 3 ----\n\n");
				printf("**  Find all products sold in the past year. **\n");

				printf("Enter year : ");
				scanf("%s", year);
				if (year[0] == '0') break;

				memset(query, 0, sizeof(query));
				sprintf(query, "select distinct (product_ID), product_name from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31'",year,year);

				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("\nProduct_ID      Product_name\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s      %12s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				while (1) {
					printf("\n\n");
					printf("---- Subtypes in TYPE 3 ----\n");
					printf("\t1. TYPE 3-1\n");
					printf("\t2. TYPE 3-2\n");
					printf("\t0. QUIT\n");
					printf("----------------------------\n");
					printf("Select Number : ");
					scanf(" %d", &subtype);
					if (subtype == 0) break;
					if (subtype == 1) {
						printf("\n\n---- TYPE 3-1 ----\n\n");
						printf("**  Then find the top k products by dollar-amount sold.  **\n");
						printf(" Which K? : ");
						scanf(" %d", &k);
						getchar();
						memset(query, 0, sizeof(query));
						sprintf(query, "select product_ID, product_name, sum(quantity*product_price) as total_price from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' group by product_ID order by total_price desc limit %d", year,year,k);

						state = 0;
						state = mysql_query(connection, query);
						int num = 1;
						if (state == 0)
						{
							printf("\nNo. Product_ID  Product_name  Total amount\n");
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%3d %10s  %12s  %12s\n", num++, sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype == 2) {
						printf("\n\n---- TYPE 3-2 ----\n\n");
						printf("**   And then find the top 10%% products by dollar-amount sold. **\n");
						memset(query, 0, sizeof(query));
						sprintf(query, "with tb as(select product_ID, product_name, sum(quantity*product_price) as total_price from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' group by product_ID order by total_price desc) select * from(select product_ID, product_name, total_price, percent_rank() over (order by total_price desc)*100 as per from tb) a where per <=10",year,year);

						state = 0;
						state = mysql_query(connection, query);
						int num = 1;
						if (state == 0)
						{
							printf("\nNo. Product_ID  Product_name  Total amount\n");
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%3d %10s  %12s  %12s\n", num++, sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
					}
				}
				break;
			case 4:
				printf("\n\n");
				printf("---- TYPE 4 ----\n\n");
				printf("**  Find all products by unit sales in the past year. **\n");

				printf("Enter year : ");
				scanf("%s", year);
				if (year[0] == '0') break;

				memset(query, 0, sizeof(query));
				sprintf(query, "select product_ID, product_name, sum(quantity) from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' group by product_ID;",year,year);
				state = 0;
				state = mysql_query(connection, query);

				if (state == 0)
				{
					printf("\nProduct_ID  Product_name  Quantity\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s  %12s  %8s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				printf("\n\n");
				while (1) {
					printf("\n\n");
					printf("---- Subtypes in TYPE 4 ----\n");
					printf("\t1. TYPE 4-1\n");
					printf("\t2. TYPE 4-2\n");
					printf("\t0. QUIT\n");
					printf("----------------------------\n");
					printf("Select Number : ");
					scanf(" %d", &subtype);
					if (subtype == 0) break;
					if (subtype == 1) {
						printf("\n\n---- TYPE 4-1 ----\n\n");
						printf("**  Then find the top k products by unit sales.  **\n");
						printf(" Which K? : ");
						scanf(" %d", &k);
						getchar();
						memset(query, 0, sizeof(query));
						sprintf(query, "select product_ID, product_name, sum(quantity) as total_q from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' group by product_ID order by total_q desc limit %d;", year,year,k);

						state = 0;
						state = mysql_query(connection, query);
						int num = 1;
						if (state == 0)
						{
							printf("\nNo. Product_ID  Product_name  Quantity\n");
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%3d %10s  %12s  %8s\n", num++, sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype == 2) {
						printf("\n\n---- TYPE 4-2 ----\n\n");
						printf("**    And then find the top 10%% products by unit sales. **\n");
						memset(query, 0, sizeof(query));
						sprintf(query, "with tb as (select product_ID,  product_name, sum(quantity) as total_quantity from order_info natural join comprise natural join product where date(order_date) between '%s-01-01' and '%s-12-31' group by product_ID order by total_quantity desc) select * from(select product_ID,  product_name, total_quantity, percent_rank() over (order by total_quantity desc)*100 as per from tb) a where per <= 10",year,year);

						state = 0;
						state = mysql_query(connection, query);
						int num = 1;
						if (state == 0)
						{
							printf("\nNo. Product_ID  Product_name  Quantity\n");
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%3d %10s  %12s  %8s\n", num++, sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
					}
				}
				break;
			case 5:
				printf("\n\n");
				printf("---- TYPE 5 ----\n\n");
				printf("**  Find those products that are out-of-stock at every store in California. **\n");

				char location[20];
				printf("Enter location of store : ");
				scanf("%s", location);
				if (location[0] == '0') break;

				memset(query, 0, sizeof(query));
				sprintf(query, "select product_ID, product_name from store natural join warehouse natural join product where inventory = 0 and warehouse_location = '%s';", location);
				state = 0;
				state = mysql_query(connection, query);


				if (state == 0)
				{
					printf("\Product_ID  Product_name\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s  %12s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}

				break;
			case 6:
				printf("\n\n");
				printf("---- TYPE 6 ----\n\n");
				printf("**  Find those packages that were not delivered within the promised time. **\n\n");

				
				memset(query, 0, sizeof(query));
				sprintf(query, "select product_ID, product_name, shipment_date, completion_date from order_info natural join shipment natural join comprise natural join product where product_ID > 100 and date(shipment_date) < date(completion_date);");
				state = 0;
				state = mysql_query(connection, query);

				if (state == 0)
				{
					printf("\Product_ID  Products(Package)  Expected date  Completion date  \n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s  %17s  %13s  %15s\n", sql_row[0],sql_row[1], sql_row[2], sql_row[3]);
					}
					mysql_free_result(sql_result);
				}
				break;
			case 7:
				printf("\n\n");
				printf("---- TYPE 7 ----\n\n");
				printf("**  Generate the bill for each customer for the past month. **\n");

				FILE* op;
				char bill[100]; char month[10];
				printf("Enter month : ");
				scanf("%s", month);
				if (month[0] == '0') break;

				memset(query, 0, sizeof(query));
				sprintf(query, "select distinct customer_ID, customer_name, accountnumber from order_info natural join contractor natural join customer where date(order_date) between '%d-%s-01' and '%d-%s-31'", t->tm_year + 1900,  month, t->tm_year + 1900, month);
				state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{	
					printf("\nGenerate bill for the following customer_ID list\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{	
						printf("%s  ", sql_row[0]);
						memset(query, 0, sizeof(query));
						sprintf(query, "select product_ID, product_name, product_price, quantity, (product_price*quantity) as tot_price from order_info natural join contractor natural join comprise natural join product natural join customer where date(order_date) between '%d-%s-01' and '%d-%s-31' and customer_ID = '%s'", t->tm_year + 1900, month, t->tm_year + 1900, month, sql_row[0]);
						state = 0;
						state = mysql_query(connection, query);
						if (state == 0)
						{
							sql_result2 = mysql_store_result(connection);
							while ((sql_row2 = mysql_fetch_row(sql_result2)) != NULL)
							{
								sprintf(bill, "Bill_%s_2022_%s.txt", sql_row[1], month);
								op = fopen(bill, "w");
								fprintf(op, "Billing details for %d-%s\nCustomer ID : %s, Name : %s, Accountnumber : %s\n", t->tm_year + 1900, month, sql_row[0], sql_row[1], sql_row[2]);
								fprintf(op, "Product_ID  Product_name  Price  Quantity  tot_price\n");
								fprintf(op, "%10s  %12s  %5s  %8s  %9s\n", sql_row2[0], sql_row2[1], sql_row2[2], sql_row2[3], sql_row2[4]);
								fclose(op);
							}
							mysql_free_result(sql_result2);
						}
					}
					mysql_free_result(sql_result);
					printf("\n\n**  Completed to generate bill. **\n");
				}

				break;
			default:
				printf("\n\n**  Invalid input. Try again. **\n");
				break;
			}

		}


		FILE* fp2 = fopen("20160530_2.txt", "r");
		char* buffer2 = NULL;

		fseek(fp2, 0, SEEK_END);
		size = ftell(fp2);
		buffer2 = (char*)malloc(size + 1);
		memset(buffer2, 0, size + 1);
		fseek(fp2, 0, SEEK_SET);
		fread(buffer2, size, 1, fp2);


		const char* del = strtok(buffer2, ";");
		while (del != NULL) {
			state = 0;
			state = mysql_query(connection, del);
			del = strtok(NULL, ";");
		}
		printf("\n**  Completed to delete tuple and drop table. **\n");
		printf("Exit Program\n");

		mysql_close(connection);
		fclose(fp2);
		free(buffer2);
	}
	fclose(fp);
	free(buffer);

	return 0;
}