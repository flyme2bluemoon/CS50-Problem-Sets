-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables

.schema crime_scene_reports
SELECT * FROM crime_scene_reports WHERE month=7 AND day=28 AND street="Chamberlin Street";
-- 295|2020|7|28|Chamberlin Street|Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

.schema interviews
SELECT * FROM interviews WHERE month=7 AND day=28;
-- 158|Jose|2020|7|28|“Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- 159|Eugene|2020|7|28|“I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- 160|Barbara|2020|7|28|“You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- 161|Ruth|2020|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2020|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163|Raymond|2020|7|28|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- LOOKING FOR EVIDENCE RELATING TO FLIGHTS

SELECT * FROM airports;
-- 1|ORD|O'Hare International Airport|Chicago
-- 2|PEK|Beijing Capital International Airport|Beijing
-- 3|LAX|Los Angeles International Airport|Los Angeles
-- 4|LHR|Heathrow Airport|London
-- 5|DFS|Dallas/Fort Worth International Airport|Dallas
-- 6|BOS|Logan International Airport|Boston
-- 7|DXB|Dubai International Airport|Dubai
-- 8|CSF|Fiftyville Regional Airport|Fiftyville
-- 9|HND|Tokyo International Airport|Tokyo
-- 10|CDG|Charles de Gaulle Airport|Paris
-- 11|SFO|San Francisco International Airport|San Francisco
-- 12|DEL|Indira Gandhi International Airport|Delhi

.schema flights
SELECT * FROM flights WHERE month=7 AND day=29 AND origin_airport_id=8 ORDER BY hour, minute;
-- 36|8|4|2020|7|29|8|20
-- 43|8|1|2020|7|29|9|30
-- 23|8|11|2020|7|29|12|15
-- 53|8|9|2020|7|29|15|20
-- 18|8|6|2020|7|29|16|0

SELECT * FROM airports WHERE id=4;
-- 4|LHR|Heathrow Airport|London

.schema passengers
SELECT * FROM passengers WHERE flight_id=36;
-- 36|7214083635|2A
-- 36|1695452385|3B
-- 36|5773159633|4A
-- 36|1540955065|5C
-- 36|8294398571|6C
-- 36|1988161715|6D
-- 36|9878712108|7A
-- 36|8496433585|7B

.schema people
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id=36);
-- 395717|Bobby|(826) 555-1652|9878712108|30G67EN
-- 398010|Roger|(130) 555-0289|1695452385|G412CB7
-- 449774|Madison|(286) 555-6063|1988161715|1106N58
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
-- 651714|Edward|(328) 555-1152|1540955065|130LD9Z
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X
-- 953679|Doris|(066) 555-9701|7214083635|M51FA04

-- LOOKING FOR EVIDENCE RELATING TO THE ATM WITHDRAWAL

.schema atm_transactions
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND atm_location="Fifer Street" and transaction_type="withdraw";
-- 246|28500762|2020|7|28|Fifer Street|withdraw|48
-- 264|28296815|2020|7|28|Fifer Street|withdraw|20
-- 266|76054385|2020|7|28|Fifer Street|withdraw|60
-- 267|49610011|2020|7|28|Fifer Street|withdraw|50
-- 269|16153065|2020|7|28|Fifer Street|withdraw|80
-- 275|86363979|2020|7|28|Fifer Street|deposit|10
-- 288|25506511|2020|7|28|Fifer Street|withdraw|20
-- 313|81061156|2020|7|28|Fifer Street|withdraw|30
-- 336|26013199|2020|7|28|Fifer Street|withdraw|35

.schema bank_accounts
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND atm_location="Fifer Street" and transaction_type="withdraw");
-- 49610011|686048|2010
-- 26013199|514354|2012
-- 16153065|458378|2012
-- 28296815|395717|2014
-- 25506511|396669|2014
-- 28500762|467400|2014
-- 76054385|449774|2015
-- 81061156|438727|2018

.schema people
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND atm_location="Fifer Street" and transaction_type="withdraw"));
-- 395717|Bobby|(826) 555-1652|9878712108|30G67EN
-- 396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
-- 438727|Victoria|(338) 555-6650|9586786673|8X428L0
-- 449774|Madison|(286) 555-6063|1988161715|1106N58
-- 458378|Roy|(122) 555-4581|4408372428|QX4YZN3
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X
-- 948985|Robert|(098) 555-1164|8304650265|I449449

-- LOOKING FOR INFORMATION RELATED TO THE PHONE CALL

.schema phone_calls
SELECT * FROM phone_calls WHERE month=7 AND day=28 AND duration<60;
-- 221|(130) 555-0289|(996) 555-8899|2020|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2020|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2020|7|28|45
-- 251|(499) 555-9472|(717) 555-1342|2020|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2020|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2020|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2020|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2020|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2020|7|28|54

.schema people
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month=7 AND day=28 AND duration<60);
-- 395717|Bobby|(826) 555-1652|9878712108|30G67EN
-- 398010|Roger|(130) 555-0289|1695452385|G412CB7
-- 438727|Victoria|(338) 555-6650|9586786673|8X428L0
-- 449774|Madison|(286) 555-6063|1988161715|1106N58
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X
-- 907148|Kimberly|(031) 555-6622|9628244268|Q12B3Z3

-- LOOKING AT INFORMATION RELATED TO THE COURT HOUSE

.schema courthouse_security_logs
SELECT * FROM courthouse_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute<30 AND activity="exit";
-- 260|2020|7|28|10|16|exit|5P2BI95
-- 261|2020|7|28|10|18|exit|94KL13X
-- 262|2020|7|28|10|18|exit|6P58WS2
-- 263|2020|7|28|10|19|exit|4328GD8
-- 264|2020|7|28|10|20|exit|G412CB7
-- 265|2020|7|28|10|21|exit|L93JTIZ
-- 266|2020|7|28|10|23|exit|322W7JE
-- 267|2020|7|28|10|23|exit|0NTHK55

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute<30 AND activity="exit");
-- 221103|Patrick|(725) 555-4692|2963008352|5P2BI95
-- 243696|Amber|(301) 555-4174|7526138472|6P58WS2
-- 396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Roger|(130) 555-0289|1695452385|G412CB7
-- 449774|Madison|(286) 555-6063|1988161715|1106N58
-- 467400|Danielle|(389) 555-5198|8496433585|4328GD8
-- 514354|Russell|(770) 555-1861|3592750733|322W7JE
-- 560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- FINAL QUERY
.schema people
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id=36) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND atm_location="Fifer Street" and transaction_type="withdraw")) AND phone_number IN (SELECT caller FROM phone_calls WHERE month=7 AND day=28 AND duration<60) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute<30 AND activity="exit");
-- 686048|Ernest|(367) 555-5533|5773159633|94KL13X

-- TO FIND ACCOMPLIST

SELECT * FROM phone_calls WHERE caller="(367) 555-5533" AND month=7 AND day=28 AND duration<60;
--233|(367) 555-5533|(375) 555-8161|2020|7|28|45

SELECT * FROM people WHERE phone_number="(375) 555-8161";
-- 864400|Berthold|(375) 555-8161||4V16VO0