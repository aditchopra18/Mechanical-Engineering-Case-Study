# Mechanical-Engineering-Case-Study
## Problem Statement
The goal of this assignment is to develop a software to generate a computer simulation of wind speed for a flight simulator. The wind speed can be assumed as an average value and a gust value added to this average. The software also incorporates storms (high speed winds) and microbursts (very high speed but short-timed storms which increase the wind speed dramatically). The software reads the data of wind simulation and on the basis of storm probability creates storms and stores it in a file. Same is done for microbursts and another file is created. Finally, an output file is created which displays the final wind speeds with time.

## Gathering of Relevant Information
The wind speed of a particular region can be represented as an average speed and an average gust (gust) value. The wind speed is in between a maximum speed (which is average speed + average gust value) and a minimum speed (which is average speed – average gust value). For example, the wind speed might be 10 miles per hour, with added noise (which represents gusts) of 5 miles per hour, the wind speed would be a value between 5 and 15 (10 ±5). The wind speed is a random number between the (average speed + gust value) and the (average speed - gust value).\
Now, a storm generates at any time between the simulation duration. During the storm duration, microbursts can also be generated which are super-high speed winds and occur only during storm duration. They have a probability of occuring, and on the basis of it, microbursts happen.\
Computers produce random numbers using specialized algorithms. Currently, because the outcomes of algorithms may be anticipated, these numbers are termed pseudo-random, and the software that generates them is known as pseudo-random number generators. The issue with such generators is that their results become very predictable with time, necessitating the use of really random generators. Using external, rapidly-changing data, truly random number generators are built. For instance, one technique to generate really random integers is to use the system time, which continues changing every millisecond.\
The occurrence of storms and microbursts is contingent on probability. Checking this probability involves generating random integers between 0 and 1 and comparing them to the supplied probability. If the requirement is met, then storms and microbursts will be produced.

## Input/Output Description
<>

The program accepts input from a file "simulationConfiguration.txt", which has data in the following manner:

<>

This data is stored in three separate arrays- wind [], storm [], burst []. We now create three other files- WindSpeedData.txt, StormData.txt and BurstData.txt. The program according to random probabilities calculates wind speeds, storm speeds, and burst speeds and stores the data along with the time in WindSpeedData.txt, StormData.txt, BurstData.txt respectively. A final wind speed is calculated by adding the respective array values from the three arrays. This final wind speed is now stored along with time in the fourth file WindSimulator.txt.\
Now, we can copy the data in all the 4 files and paste it in excel to draw Wind Speed graphs.

## Test Case
(Data is entered in file by the user only and output is stored not in the C++ output window, but in files. For ease of use, here only the data is shown as stored in files.)

In file WindSpeedData.txt\
0 13\
1 14\
2 14\
3 6\
4 12\
5 10\
6 10\
7 15\
8 6\
9 5\
10 12\
11 12\
12 10\
13 13\
14 11\
15 12\
16 8\
17 12\
18 14\
19 7\
20 12\
21 12\
22 13\
23 15\
24 11\
25 12\
26 13\
27 10\
28 11\
29 12\
30 7\
31 6\
32 14\
33 15\
34 15\
35 7\
36 9\
37 14\
38 12\
39 10\
40 9\
41 12\
42 10\
43 11\
44 12\
45 5\
46 10\
47 5\
48 10\
49 9\
50 10\
51 6\
52 8\
53 15\
54 11\
55 5\
56 5\
57 11\
58 12\
59 13\
60 12

In file StormData.txt\
0 0\
1 47\
2 55\
3 54\
4 55\
5 48\
6 55\
7 46\
8 46\
9 51\
10 53\
11 50\
12 50\
13 47\
15 0\
16 0\
17 0\
18 0\
19 0\
20 0\
21 0\
22 0\
23 51\
24 50\
25 52\
26 49\
27 45\
28 53\
29 49\
30 49\
31 45\
32 48\
33 48\
34 50\
35 53\
36 49\
37 52\
38 53\
39 47\
41 0\
42 52\
43 49\
44 46\
45 50\
46 47\
47 52\
48 54\
49 45\
50 55\
51 48\
52 53\
53 49\
54 46\
55 51\
56 47\
57 54\
58 47\
59 48\
60 0

In File BurstData.txt\
0 0\
1 0\
2 0\
3 0\
4 0\
5 134\
6 98\
7 148\
8 104\
9 148\
10 147\
11 102\
12 0\
13 0\
14 0\
15 0\
16 0\
17 0\
18 0\
19 0\
20 0\
21 0\
22 0\
23 0\
24 0\
25 0\
26 0\
27 0\
28 0\
29 0\
30 0\
31 0\
32 0\
33 0\
34 100\
35 136\
36 107\
37 0\
38 125\
39 98\
40 115\
41 105\
42 142\
43 131\
44 105\
45 107\
46 113\
47 105\
48 0\
49 121\
50 131\
51 130\
52 111\
53 138\
54 110\
55 109\
56 116\
57 113\
58 136\
59 127\
60 143

In file WindSimulator.txt\
0 26\
1 75\
2 83\
3 66\
4 79\
5 68\
6 75\
7 76\
8 58\
9 61\
10 77\
11 74\
12 70\
13 73\
14 22\
15 24\
16 16\
17 24\
18 28\
19 14\
20 24\
21 24\
22 77\
23 80\
24 74\
25 73\
26 71\
27 73\
28 71\
29 73\
30 59\
31 60\
32 76\
33 80\
34 83\
35 63\
36 70\
37 81\
38 71\
39 20\
40 70\
41 73\
42 66\
43 72\
44 71\
45 62\
46 74\
47 55\
48 75\
49 66\
50 73\
51 61\
52 62\
53 81\
54 69\
55 64\
56 57\
57 70\
58 24\
59 26\
60 24
