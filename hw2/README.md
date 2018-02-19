# Playing with Big Data

You are asked to design and implement a data structure to store a very big data set of KDDCup 2012
Track 2. KDDCup is an international data mining competition, and our dear NTU team won the
champion of track 2 that year. There are 149639105 lines in the file

``
/tmp2/KDDCUP2012/track2/kddcup2012track2.txt,
``

which is placed on 217 workstations from linux1 to linux8. The detailed description of the data set is
here: http://www.kddcup2012.org/c/kddcup2012-track2 . In particular, the format of each line is:

``
(Click)\t(Impression)\t(DisplayURL)\t(AdID)\t(AdvertiserID)\t(Depth)\t(Position)\t
(QueryID)\t(KeywordID)\t(TitleID)\t(DescriptionID)\t(UserID)
``

The data set is a log file of Tencent Ad system. Each line means that an user (UserID) is shown with
an ad (AdID) at location (Postition)-(Depth) upon querying (QueryID); the ad is shown for (Impression)
number of times, and clicked for (Click) number of times; the ad is of properties (DisplayURL), (AdvertiserID),
(KeywordID), (TitleID), (DescriptionID). You can view the data set as a super big 5D sparse
matrix M with M[UserID][AdID][QueryID][Position][Depth]=(Click, Impression) along with some
side information per (AdID).

Your design should support the following actions:
- • get(u, a, q, p, d): output (Click, Impression) at M[UserID][AdID][QueryID][Position][Depth]
- • clicked(u): output all (AdID, QueryID) pairs that user u has made at least one click
- • impressed(u1, u2): output the sorted (AdID), line by line, and its associated properties (DisplayURL),
(AdvertiserID), (KeywordID), (TitleID), (DescriptionID) that both users u1 and u2
has at least one impression on
- • profit(a, ✓): output the sorted (UserID), line by line, whose click-through-rate (total click / total
impression) on a is greater than or equal to ✓. Note that 0/0 is defined as 0.
