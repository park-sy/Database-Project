# Database-Project

프로젝트 개요

가상의 Electronics Vendor company의 DBA라고 가정한다. 이 회사에서는 회사 운영의 기초가 되는 데이터베이스의 주요 부분을 재설하기로 결정했고, 설계 제안을 요청하는 관리자는 컴퓨터에 대해 잘 알지 못하고, 기술 수준에서 매우 상세한 사양을 제공할 수 없다. 때문에 요구사항을 분석하고 주어진 질의에 적절하게 대응할 수 있도록 데이터베이스 설계 제안서를 작성해야 한다.

E-R diagram
![image](https://user-images.githubusercontent.com/53611554/193028581-b6933e92-8e23-487d-8b5a-f37c57075b6e.png)

Schema diagram
![image](https://user-images.githubusercontent.com/53611554/193028739-7eb70965-b15a-48dc-a782-2689093d0267.png)

Query
(TYPE 1) Assume the package shipped by USPS with tracking number X is reported to have been destroyed in an accident. Find the contact information for the customer.
![image](https://user-images.githubusercontent.com/53611554/193029229-65b4ccd8-e966-4de5-81c8-34c5ac56aaea.png)
<img src="[이미지주소](https://user-images.githubusercontent.com/53611554/193029229-65b4ccd8-e966-4de5-81c8-34c5ac56aaea).png" width="200" height="400"/>

• (TYPE 1-1) Then find the contents of that shipment and create a new shipment of replacement items.
![image](https://user-images.githubusercontent.com/53611554/193029252-7084a429-c731-4a75-aeda-f740c991a4d1.png)

• (TYPE 2) Find the customer who has bought the most (by price) in the past year.
![image](https://user-images.githubusercontent.com/53611554/193029274-e9d5ae15-b4bb-4800-839a-d5946aba0c8e.png)

• (TYPE 2-1) Then find the product that the customer bought the most.
![image](https://user-images.githubusercontent.com/53611554/193029319-4d53b490-c1db-4dd7-ae06-382c4e986773.png)

• (TYPE 3) Find all products sold in the past year.
![image](https://user-images.githubusercontent.com/53611554/193029349-8066956e-f0d9-40c2-b177-c85a692abddf.png)

• (TYPE 3-1) Then find the top k products by dollar-amount sold.
![image](https://user-images.githubusercontent.com/53611554/193029374-ebf3c1f3-450f-41dc-a556-6ec9c32d2647.png)

• (TYPE 3-2) And then find the top 10% products by dollar-amount sold.
![image](https://user-images.githubusercontent.com/53611554/193029404-15353290-257c-4424-9841-75af4014ab23.png)

• (TYPE 4) Find all products by unit sales in the past year.
![image](https://user-images.githubusercontent.com/53611554/193029437-067eb75e-a77e-4a29-af46-ad822500928f.png)

• (TYPE 4-1) Then find the top k products by unit sales.
![image](https://user-images.githubusercontent.com/53611554/193029473-f886fee7-3f38-4a67-b6f0-0e51526b635d.png)

• (TYPE 4-2) And then find the top 10% products by unit sales.
![image](https://user-images.githubusercontent.com/53611554/193029499-6d3b41cd-ab46-45f9-982f-bcb248627244.png)

• (TYPE 5) Find those products that are out-of-stock at every store in California.
![image](https://user-images.githubusercontent.com/53611554/193029533-24022e1a-1a67-4f9d-a801-18cf31103e94.png)

• (TYPE 6) Find those packages that were not delivered within the promised time.
![image](https://user-images.githubusercontent.com/53611554/193029557-9cedc799-db5f-416e-9522-67fd63531151.png)

• (TYPE 7) Generate the bill for each customer for the past month.
![image](https://user-images.githubusercontent.com/53611554/193029575-a05fd14e-8d95-4221-867a-8e1e795accac.png)
![image](https://user-images.githubusercontent.com/53611554/193029608-f67c21bf-0657-406c-9a65-10e5ae358071.png)
![image](https://user-images.githubusercontent.com/53611554/193029618-b045d047-cbcc-4dea-9b7a-711016a3e366.png)

자세한 쿼리와 설명은 [여기](https://github.com/park-sy/Database-Project/blob/main/db_p2/%5Bproject2%5D20160530.pdf)서 보실 수 있습니다.


