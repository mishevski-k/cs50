-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Case Information: took place on July 28, 2023 on Humphrey Street, The Thief had a accomplice and escaped the city

-- 1.Map out the database schemans and tables

.tables 
-- airports              crime_scene_reports   people
-- atm_transactions      flights               phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers
.schema airports -- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
.schema crime_scene_reports -- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
.schema people -- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
.schema atm_transactions -- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
.schema flights -- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
.schema phone_calls -- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
.schema bakery_security_logs -- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
.schema interviews -- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
.schema bank_accounts -- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
.schema passengers -- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 2. Look at the crime scene reports

SELECT
    *
FROM
    crime_scene_reports
WHERE
    year = 2023
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';

-- 295|2023|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- 297|2023|7|28|Humphrey Street|Littering took place at 16:36. No known witnesses.
-- We can three witnesses for the bakery robbery, they were interviwed and all 3 transcibes mentioned the bakery which we can use to get the correct interviews

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 3. Look at the interviews that took place on the day of the theft which mentioned the bakery

SELECT
    *
FROM
    interviews
WHERE
    year = 2023
    AND month = 7
    and day = 28
    and transcript like '%bakery%';

-- 161|Ruth|2023|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2023|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|2023|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- New Case Information: The thief was spotted leaving the crime scene parking lot withing 10 minutes of the theft which we know happend at 10:15am, there are security cameras we can use to find the car
--                       The thief was spotted earlier that morning withdrawing money from the ATM, maybe we can find back activity at that ATM
--                       The thief called the accomplice to arange a flight ticket out of the city, he asked the earliest flith the next day and for the accomplice to buy them, the call lasted less than 1 minut, we should check phone records regarding this

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 4. Look at the bakery security logs for cars that have left the parking lot withing 10 minutes of the robbery, and map people to the cars license plates 

SELECT
    *
FROM
    bakery_security_logs
WHERE
    year = 2023
    AND month = 7
    and day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
    AND activity = 'exit';

-- 260|2023|7|28|10|16|exit|5P2BI95
-- 261|2023|7|28|10|18|exit|94KL13X
-- 262|2023|7|28|10|18|exit|6P58WS2
-- 263|2023|7|28|10|19|exit|4328GD8
-- 264|2023|7|28|10|20|exit|G412CB7
-- 265|2023|7|28|10|21|exit|L93JTIZ
-- 266|2023|7|28|10|23|exit|322W7JE
-- 267|2023|7|28|10|23|exit|0NTHK55

-- Using the security footage we can map cars to people using the license_plate which we can use later on to narrow our search

SELECT
    *
FROM
    people
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
            AND activity = 'exit'
    );

-- 221103|Vanessa|(725) 555-4692|2963008352|5P2BI95
-- 243696|Barry|(301) 555-4174|7526138472|6P58WS2
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 5.Look at the atm activity that day and map the transactions to the correct person that withdrew money on the day of the robbery

SELECT
    *
FROM
    atm_transactions
WHERE
    year = 2023
    AND month = 7
    AND day = 28
    and transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street';

-- 246|28500762|2023|7|28|Leggett Street|withdraw|48
-- 264|28296815|2023|7|28|Leggett Street|withdraw|20
-- 266|76054385|2023|7|28|Leggett Street|withdraw|60
-- 267|49610011|2023|7|28|Leggett Street|withdraw|50
-- 269|16153065|2023|7|28|Leggett Street|withdraw|80
-- 288|25506511|2023|7|28|Leggett Street|withdraw|20
-- 313|81061156|2023|7|28|Leggett Street|withdraw|30
-- 336|26013199|2023|7|28|Leggett Street|withdraw|35

SELECT
    *
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 28
                    AND transaction_type = 'withdraw'
                    AND atm_location = 'Leggett Street'
            )
    );

-- 395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 438727|Benista|(338) 555-6650|9586786673|8X428L0
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 458378|Brooke|(122) 555-4581|4408372428|QX4YZN3
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Using the gatherd person data maybe we can narrow our search of people that retrieved money that morning and left the parking lot after the robbeery

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 6.Narrow the person search

SELECT
    *
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 28
                    and transaction_type = 'withdraw'
                    and atm_location = 'Leggett Street'
            )
    )
    AND license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= '15'
            AND minute <= '25'
            AND activity = 'exit'
    );

-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Now we have a very narrowed down suspect set which we can use to find calls and flight activity to get our thief

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 7.Get calls for that day that lasted 60 seconds or less

SELECT
    *
FROM
    phone_calls
WHERE
    year = 2023
    AND month = 7
    AND day = 28
    and duration <= 60;

-- 221|(130) 555-0289|(996) 555-8899|2023|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2023|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2023|7|28|45
-- 234|(609) 555-5876|(389) 555-5198|2023|7|28|60
-- 251|(499) 555-9472|(717) 555-1342|2023|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2023|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2023|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2023|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2023|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2023|7|28|54

-- Using the raw dataset we can find callers and recievers for that day, Note that our thief called someone to arange the tickets so he is the caller and the reciever is the accomplice

-- CALLER
SELECT
    *
FROM
    people
WHERE
    phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            and duration <= 60
    );

-- 395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 438727|Benista|(338) 555-6650|9586786673|8X428L0
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 561160|Kathryn|(609) 555-5876|6121106406|4ZY7I8T
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
-- 907148|Carina|(031) 555-6622|9628244268|Q12B3Z3

-- RECIEVER
SELECT
    *
FROM
    people
WHERE
    phone_number IN (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            and duration <= 60
    );

-- 250277|James|(676) 555-6554|2438825627|Q13SVG6
-- 251693|Larry|(892) 555-8872|2312901747|O268ZZ0
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 484375|Anna|(704) 555-2131||
-- 567218|Jack|(996) 555-8899|9029462229|52R0Y8U
-- 626361|Melissa|(717) 555-1342|7834357192|
-- 712712|Jacqueline|(910) 555-3251||43V0R5D
-- 847116|Philip|(725) 555-3243|3391710505|GW362R6
-- 864400|Robin|(375) 555-8161||4V16VO0
-- 953679|Doris|(066) 555-9701|7214083635|M51FA04

SELECT
    *
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 28
                    and transaction_type = 'withdraw'
                    and atm_location = 'Leggett Street'
            )
    )
    AND license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= '15'
            AND minute <= '25'
            AND activity = 'exit'
    )
    AND phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            and duration <= 60
    );

-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- We have succesfully narrowed our search two two people, next will be to check airports for all flights out of fiftyviller the next day after the robbery

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 8.Check Airport data for flights leading out of fiftyville the next day

SELECT
    *
from
    airports
WHERE
    city = 'Fiftyville';

-- 8|CSF|Fiftyville Regional Airport|Fiftyville

-- One airport which we can use to list flights that day

SELECT
    *
from
    flights
WHERE
    year = 2023
    AND month = 7
    AND day = 29
    and origin_airport_id = (
        SELECT
            id
        FROM
            airports
        WHERE
            city = 'Fiftyville'
    )
ORDER BY
    hour
limit
    1;

-- 36|8|4|2023|7|29|8|20

-- NOTE: Per Phone call we wanted to arrange the first flight out of the city but we dont know if we did take it, we will the first flight and if no results are given we will try the other ones aswell

SELECT
    *
FROM
    passengers
WHERE
    flight_id IN (
        SELECT
            id
        from
            flights
        WHERE
            year = 2023
            AND month = 7
            AND day = 29
            and origin_airport_id = (
                SELECT
                    id
                FROM
                    airports
                WHERE
                    city = 'Fiftyville'
            )
        ORDER BY
            hour
        limit
            1
    );

-- 36|7214083635|2A
-- 36|1695452385|3B
-- 36|5773159633|4A
-- 36|1540955065|5C
-- 36|8294398571|6C
-- 36|1988161715|6D
-- 36|9878712108|7A
-- 36|8496433585|7B

-- We can enhance the data by mapping the passengers to a person

SELECT
    *
FROM
    people
WHERE
    passport_number IN (
        SELECT
            passport_number
        FROM
            passengers
        WHERE
            flight_id IN (
                SELECT
                    id
                from
                    flights
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 29
                    and origin_airport_id = (
                        SELECT
                            id
                        FROM
                            airports
                        WHERE
                            city = 'Fiftyville'
                    )
                ORDER BY
                    hour
                limit
                    1
            )
    );

-- 395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 651714|Edward|(328) 555-1152|1540955065|130LD9Z
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
-- 953679|Doris|(066) 555-9701|7214083635|M51FA04

-- Using this enhanced data we can continue and narrow the person search to just one person

SELECT
    *
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 28
                    and transaction_type = 'withdraw'
                    and atm_location = 'Leggett Street'
            )
    )
    AND license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= '15'
            AND minute <= '25'
            AND activity = 'exit'
    )
    AND phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            and duration <= 60
    )
    and passport_number IN (
        SELECT
            passport_number
        FROM
            passengers
        WHERE
            flight_id IN (
                SELECT
                    id
                from
                    flights
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 29
                    and origin_airport_id = (
                        SELECT
                            id
                        FROM
                            airports
                        WHERE
                            city = 'Fiftyville'
                    )
                ORDER BY
                    hour
                limit
                    1
            )
    );

-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Now That we know that our suspect is on the first flight leaving we can get data for the airport we is going to land

SELECT
    *
FROM
    airports
WHERE
    id = (
        SELECT
            destination_airport_id
        from
            flights
        WHERE
            year = 2023
            AND month = 7
            AND day = 29
            and origin_airport_id = (
                SELECT
                    id
                FROM
                    airports
                WHERE
                    city = 'Fiftyville'
            )
        ORDER BY
            hour
        limit
            1
    );

-- 4|LGA|LaGuardia Airport|New York City

-- New Case Information: During the forensic investigation we have found that Bruce's car with the number plate 94KL13X left the crimescene withing 10 minutes of the robbery,
--                       He has atm activity that day on the street the whitness mentioned,
--                       Call logs show he did call someone and the call took less than 1 minute like another whitness mentioned,
--                       And he is a passenger using his passport 5773159633 on the first flight leaving the city the next day
-- With very good certainty we can say that Bruce is our criminal but we whould need to find the buyer of the tickers which we know is the reciever of the call the day of the robbery, with that part finished we would have crossed all question marks of this case

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- 9.Check calls activity to find our accomplice using Bruce's phone number

SELECT
    *
FROM
    people
WHERE
    phone_number IN (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            and duration <= 60
            AND caller = '(367) 555-5533'
    );

-- 864400|Robin|(375) 555-8161||4V16VO0

-- // -- // -- // -- // -- // -- // -- // -- // -- // -- // --

-- New Case Information: After the robbery Bruce called Robin to arange flight tickers leaving Fiftyville For New York City on the 29 Of July 2023 at 8:20am