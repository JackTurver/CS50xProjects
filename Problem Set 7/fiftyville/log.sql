-- Keep a log of any SQL queries you execute as you solve the mystery.

--Start by looking at the crime scene report from the day of the theft.
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';
--| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
--| Littering took place at 16:36. No known witnesses.

--Now look at the interviews conducted on the same day for the 3 witnesses. Looking for each of these interviews to mention the bakery
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE ('%bakery%');
--| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

--From this we know the theft happened at the bakery and so the baker security logs around 10:15am are important
--Checking the ATM logs < 10:15am will show the possible thief
--Then checking the flight list for a person with the same name on the earliest flight for that destination will show the thief
--the thiefs accomplice will be the person who booked the flight and can be found by checking their bank account

SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND minute < 25 AND minute > 15 AND activity = 'exit';
--This is the list of license plates that left the scene within 10 minutes of the robbery
--| 5P2BI95       |
--| 94KL13X       |
--| 6P58WS2       |
--| 4328GD8       |
--| G412CB7       |
--| L93JTIZ       |
--| 322W7JE       |
--| 0NTHK55       |

SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND transaction_type = 'withdraw' AND atm_location = ('Leggett Street');
--| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
--| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
--| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
--| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
--| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |

SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60;
--+-----+----------------+----------------+------+-------+-----+----------+
--| id  |     caller     |    receiver    | year | month | day | duration |
--+-----+----------------+----------------+------+-------+-----+----------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
--+-----+----------------+----------------+------+-------+-----+----------+


--Can now use a combination of phone numbers from caller and bank account from atm transaction to find the person id for that person and the license plate.
--Combine this with finding that name on a flight out of fiftyville before 12pm the next day will show the culprit
--Flight ID being shows as 36
SELECT * FROM bakery_security_logs
   JOIN people ON people.license_plate = bakery_security_logs.license_plate
   JOIN bank_accounts ON people.id = bank_accounts.person_id
   JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
   JOIN phone_calls ON people.phone_number = phone_calls.caller
   JOIN passengers ON people.passport_number = passengers.passport_number
   JOIN flights ON flights.id = passengers.flight_id
   JOIN airports ON flights.origin_airport_id = airports.id
   WHERE bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.minute < 25 AND bakery_security_logs.activity = 'exit'
   AND phone_calls.duration < 60 AND phone_calls.day = 28  AND phone_calls.month = 7
   AND atm_transactions.day = 28 AND atm_transactions.month = 7 AND atm_transactions.transaction_type = 'withdraw' AND atm_transactions.atm_location = ('Leggett Street')
   AND flights.day = 29 AND flights.month = 7 AND flights.hour < 12
   AND airports.city = 'Fiftyville';

--This shows Bruce is the culprit so now we can trace his calls on the day at the right time to find the accomplice
SELECT * FROM phone_calls
   JOIN people ON people.phone_number = phone_calls.caller
   JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   WHERE bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.minute < 25 AND bakery_security_logs.activity = 'exit'
   AND phone_calls.duration < 60 AND phone_calls.day = 28  AND phone_calls.month = 7
   AND people.name = 'Bruce';

--This gives the recievers phone number as (375) 555-8161
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
--This shows the accomplice as Robin

--With flight ID as 36 we can find the destination for that flight on that day
SELECT city FROM flights
   JOIN airports ON airports.id = flights.destination_airport_id
   WHERE flights.id = 36;
   
--Says New York City was the destination