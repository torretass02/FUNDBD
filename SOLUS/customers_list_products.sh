#!/usr/bin/expect -f

set timeout -1

spawn ./menu

expect "Enter a number that corresponds to your choice > "
send -- "3\r"

expect "Enter a number that corresponds to your choice > "
send -- "2\r"

expect "Enter customer number > "
send -- "141\r"

# 7933 -> stock for product with id = S10_1678
expect "1969 Harley Davidson Ultimate Chopper 66"
expect "1952 Alpine Renault 1300 50"
expect "1996 Moto Guzzi 1100i 45"
expect "2003 Harley-Davidson Eagle Drag Bike 56"
expect "1972 Alfa Romeo GTA 26"
expect "1968 Ford Mustang 20"
expect "2001 Ferrari Enzo 20"
expect "1958 Setra Bus 49"
expect "2002 Suzuki XREO 21"
expect "1969 Corvair Monza 125"
expect "1968 Dodge Charger 59"
expect "1969 Ford Falcon 49"
expect "1970 Plymouth Hemi Cuda 44"
expect "1957 Chevy Pickup 183"
expect "1969 Dodge Charger 80"
expect "1940 Ford Pickup Truck 54"
expect "1993 Mazda RX-7 29"
expect "1937 Lincoln Berline 103"
expect "1936 Mercedes-Benz 500K Special Roadster 68"
expect "1965 Aston Martin DB5 101"
expect "1980s Black Hawk Helicopter 74"
expect "1917 Grand Touring Sedan 39"
expect "1948 Porsche 356-A Roadster 65"
expect "1995 Honda Civic 41"
expect "1998 Chrysler Plymouth Prowler 125"
expect "1911 Ford Town Car 27"
expect "1964 Mercedes Tour Bus 154"
expect "1932 Model A Ford J-Coupe 40"
expect "1926 Ford Fire Engine 77"
expect "P-51-D Mustang 70"
expect "1936 Harley Davidson El Knucklehead 36"
expect "1928 Mercedes-Benz SSK 104"
expect "1999 Indy 500 Monte Carlo SS 112"
expect "1913 Ford Model T Speedster 30"
expect "1934 Ford V8 Coupe 24"
expect "1999 Yamaha Speed Boat 112"
expect "18th Century Vintage Horse Carriage 29"
expect "1903 Ford Model A 140"
expect "1992 Ferrari 360 Spider red 308"
expect "Collectable Wooden Train 137"
expect "1969 Dodge Super Bee 55"
expect "1917 Maxwell Touring Car 36"
expect "1976 Ford Gran Torino 98"
expect "1948 Porsche Type 356 Roadster 109"
expect "1957 Vespa GS150 59"
expect "1941 Chevrolet Special Deluxe Cabriolet 56"
expect "1970 Triumph Spitfire 138"
expect "1932 Alfa Romeo 8C2300 Spider Sport 73"
expect "1904 Buick Runabout 123"
expect "1939 Cadillac Limousine 56"
expect "1957 Corvette Convertible 74"
expect "1957 Ford Thunderbird 75"
expect "1970 Chevy Chevelle SS 454 133"
expect "1970 Dodge Coronet 197"
expect "1997 BMW R 1100 S 35"
expect "1966 Shelby Cobra 427 S/C 122"
expect "1928 British Royal Navy Airplane 108"
expect "1939 Chevrolet Deluxe Coupe 64"
expect "18th century schooner 74"
expect "1938 Cadillac V-16 Presidential Limousine 90"
expect "1962 Volkswagen Microbus 140"
expect "1982 Ducati 900 Monster 83"
expect "1949 Jaguar XK 120 158"
expect "1958 Chevy Corvette Limited Edition 245"
expect "1900s Vintage Bi-Plane 63"
expect "1952 Citroen-15CV 135"
expect "1982 Lamborghini Diablo 132"
expect "1912 Ford Model T Delivery Wagon 30"
expect "1969 Chevrolet Camaro Z28 129"
expect "1971 Alpine Renault 1600s 124"
expect "1937 Horch 930V Limousine 81"
expect "2002 Chevy Corvette 174"
expect "1940 Ford Delivery Sedan 74"
expect "1956 Porsche 356A Coupe 161"
expect "Corsair F4U ( Bird Cage) 89"
expect "1936 Mercedes Benz 500k Roadster 43"
expect "1992 Porsche Cayenne Turbo Silver 161"
expect "1936 Chrysler Airflow 81"
expect "1900s Vintage Tri-Plane 96"
expect "1961 Chevrolet Impala 69"
#expect "1980âs GM Manhattan Express 41"
expect "1997 BMW F650 ST 23"
expect "1982 Ducati 996 R 124"
expect "1954 Greyhound Scenicruiser 157"
expect "1950's Chicago Surface Lines Streetcar 150"
expect "1996 Peterbilt 379 Stake Bed with Outrigger 80"
expect "1928 Ford Phaeton Deluxe 89"
expect "1974 Ducati 350 Mk3 Desmo 82"
expect "1930 Buick Marquette Phaeton 96"
expect "Diamond T620 Semi-Skirted Tanker 141"
expect "1962 City of Detroit Streetcar 145"
expect "2002 Yamaha YZR M1 40"
expect "The Schooner Bluenose 89"
expect "American Airlines: B767-300 112"
expect "The Mayflower 91"
expect "HMS Bounty 73"
expect "America West Airlines B757-200 70"
expect "The USS Constitution Ship 66"
expect "1982 Camaro Z28 73"
expect "ATA: B757-300 27"
expect "F/A 18 Hornet 1/72 59"
expect "The Titanic 126"
expect "The Queen Mary 75"
expect "American Airlines: MD-11S 79"
expect "Boeing X-32A JSF 71"
expect "Pont Yacht 113"


puts "\n--------------------------------OK\n"

expect "Enter a number that corresponds to your choice > "
send -- "4\r"

expect "Enter a number that corresponds to your choice > "
send -- "4\r"

expect eof
