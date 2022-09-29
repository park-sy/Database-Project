# Database-Project

프로젝트 개요

가상의 Electronics Vendor company의 DBA라고 가정한다. 이 회사에서는 회사 운영의 기초가 되는 데이터베이스의 주요 부분을 재설하기로 결정했고, 설계 제안을 요청하는 관리자는 컴퓨터에 대해 잘 알지 못하고, 기술 수준에서 매우 상세한 사양을 제공할 수 없다. 때문에 요구사항을 분석하고 주어진 질의에 적절하게 대응할 수 있도록 데이터베이스 설계 제안서를 작성해야 한다.

E-R diagram

![ERD2 20160530](https://user-images.githubusercontent.com/53611554/193031107-56e35e31-2c7d-41a2-b007-d57a808aafb7.png)

Schema diagram
![image](https://user-images.githubusercontent.com/53611554/193028739-7eb70965-b15a-48dc-a782-2689093d0267.png)

Query
• (TYPE 1) Assume the package shipped by USPS with tracking number X is reported to have been destroyed in an accident. Find the contact information for the customer.
  • (TYPE 1-1) Then find the contents of that shipment and create a new shipment of replacement items.

• (TYPE 2) Find the customer who has bought the most (by price) in the past year.
  • (TYPE 2-1) Then find the product that the customer bought the most.

• (TYPE 3) Find all products sold in the past year.
  • (TYPE 3-1) Then find the top k products by dollar-amount sold.
  • (TYPE 3-2) And then find the top 10% products by dollar-amount sold.

• (TYPE 4) Find all products by unit sales in the past year.
  • (TYPE 4-1) Then find the top k products by unit sales.
  • (TYPE 4-2) And then find the top 10% products by unit sales.

• (TYPE 5) Find those products that are out-of-stock at every store in California.

• (TYPE 6) Find those packages that were not delivered within the promised time.

• (TYPE 7) Generate the bill for each customer for the past month.

자세한 설명은 [여기](https://github.com/park-sy/Database-Project/blob/main/db_p2/%5Bproject2%5D20160530.pdf)서 보실 수 있습니다.


