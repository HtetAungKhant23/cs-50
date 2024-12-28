-- Keep a log of any SQL queries you execute as you solve the mystery.
/ /
-- to get crime_reports at 7/28/2023 and Humphrey Street and case description contain 'CS50 duck'
select
    *
from
    crime_scene_reports
where
    day = 28
    and month = 7
    and year = 2023
    and street = 'Humphrey Street'
    and description like '%CS50 duck%';

-- in description, i got infotmation
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
/ /
-- i knew about Theft's interviews in description of crime_reports. So, i try to get those interviews at 7/28/2023 and transcript contain 'thief'
select
    *
from
    interviews
where
    day = 28
    and month = 7
    and year = 2023
    and transcript like '%thief%';

-- in transcript, i got three informations
--
-- 1. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.
--
-- 2. I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money
--
-- 3. As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
/ /
-- to get bakery_parking_logs at 7/28/2023 and hour = 10 and minute < 25 and activity = 'exit'
select
    *
from
    bakery_security_logs
where
    day = 28
    and month = 7
    and year = 2023
    and hour = 10
    and minute < 25
    and activity = 'exit';

/ /
-- from the second informations, i got this "Earlier this morning, walking by the ATM on Leggett Street and saw the thief there withdrawing some money".
-- So, i try to get people who is withdraw from atm in Leggett Street at 7/28/2023 and bakery_parking_logs at 7/28/2023 and hour = 10 and minute < 25 and activity = 'exit'
select
    p.id,
    p.name,
    p.phone_number,
    p.passport_number,
    p.license_plate
from
    atm_transactions atm
    join bank_accounts bank on bank.account_number = atm.account_number
    join people p on p.id = bank.person_id
    join bakery_security_logs bakery on bakery.license_plate = p.license_plate
where
    bakery.day = 28
    and bakery.month = 7
    and bakery.year = 2023
    and atm_location = 'Leggett Street'
    and transaction_type = 'withdraw'
    and bakery.hour = 10
    and bakery.minute < 25
    and bakery.activity = 'exit';

/ /
-- from the final informations, i got this "Thief called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."
-- So, i try to get people who is called from brakey at 7/28/2023 less than 1 minute duration and flight 7/29/2023  and withdraw from atm in Leggett Street at 7/28/2023 and bakery_parking_logs at 7/28/2023 and hour = 10 and minute < 25 and activity = 'exit'
select distinct
    (p.id),
    p.name,
    p.phone_number,
    p.passport_number,
    p.license_plate,
    psg.flight_id,
    psg.seat,
    phone.receiver
from
    atm_transactions atm
    join bank_accounts bank on bank.account_number = atm.account_number
    join people p on p.id = bank.person_id
    join bakery_security_logs bakery on bakery.license_plate = p.license_plate
    join phone_calls phone on phone.caller = p.phone_number
    join passengers psg on psg.passport_number = p.passport_number
where
    bakery.day = 28
    and bakery.month = 7
    and bakery.year = 2023
    and atm_location = 'Leggett Street'
    and transaction_type = 'withdraw'
    and bakery.hour = 10
    and bakery.minute < 25
    and bakery.activity = 'exit'
    and phone.duration < 60
    and phone.day = 28
    and phone.month = 7
    and phone.year = 2023
    and psg.flight_id = (
        select
            id
        from
            flights
        where
            day = 29
            and month = 7
            and year = 2023
            and origin_airport_id = (
                select
                    id
                from
                    airports
                where
                    city = 'Fiftyville'
            )
        order by
            hour
        limit
            1
    );

-- and i got personal information of ACCOMPLICE from phone number
SELECT
    *
FROM
    people
WHERE
    phone_number = '(375) 555-8161';

-- I got city information of thief escaped from flight id
SELECT
    a.id,
    a.abbreviation,
    a.city,
    a.full_name
FROM
    flights f
    JOIN airports a ON a.id = f.destination_airport_id
WHERE
    f.id = 36;
