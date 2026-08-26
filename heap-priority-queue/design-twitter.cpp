#include<bits/stdc++.h>
using namespace std;

// brute force - using sorting
// tweetMap[userId] - stores { timestamp of post, postId/tweetId }
// followMap[userId] - list of all people user follows
// O(n*m + tlogt) for getNewsFeed() and O(1) for remaining methods, space : O(N*m + N * M)
// where n : total number of followeeIds with userId, m is maximum number of tweets by an user, t is total number of tweets associated with userId and its followeeIds, N is the total number of userIds and M is the maximum number of followees for any user.
/*
keep a map of user id -> time, postid
keep a map of user id -> who they follow -> so we can get the posts of whome they follow as well based on time obv
postTweet -> just insert into the map and increase the time 
follow, unfollow someone - just insert, remove 
getPosts -> first get own all posts + followees all posts 
then sort based on time and get min(10, total posts))
hence all are O(1) just getPosts() is nm -> going through each n followee and there m posts + tlogt to sort where t is total number of posts we could get - own + followees
*/
class Twitter {
private:
    int time;
    unordered_map<int, vector<pair<int, int>>> tweetMap;
    unordered_map<int, unordered_set<int>> followMap;
public:
    Twitter() : time(0) {}
    
    void postTweet(int userId, int tweetId) {
        tweetMap[userId].push_back({ time++, tweetId });
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<pair<int, int>> feed = tweetMap[userId];
        for (int followeeId : followMap[userId]) {
            feed.insert(feed.end(), tweetMap[followeeId].begin(), tweetMap[followeeId].end());
        }
        sort(feed.begin(), feed.end(), [](auto& a, auto &b) {
            return a.first > b.first;
        });
        vector<int> result;
        for (int i = 0; i < min(10, (int)feed.size()); i++) {
            result.push_back(feed[i].second);
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            followMap[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
};

/*
Optimization to this: using minheap 
we don't need to sort all the tweets btw - just get the top 10 recent ones - using minheap - top 10 recent ones stay inside and also most recent always on the top still hence now we're just
so we take each user's last tweet -> latest and then store the top -> do this 10 times - nlogn - pushing each user once atmost
O(nlogn), O(N*m, + N*M, + n) - we got extra priority queue as well
*/
class Twitter2 {
    int time;
    unordered_map<int, vector<pair<int, int>>> tweetMap;
    unordered_map<int, unordered_set<int>> followMap;

    struct compare {
        bool operator() (vector<int>& a, vector<int>& b) {
            return a[0] < b[0]; // larger time value has more priority
        }
    };
public:
    Twitter2() : time(0) {}
    
    void postTweet(int userId, int tweetId) {
        tweetMap[userId].push_back({time++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> result;
        priority_queue<vector<int>, vector<vector<int>>, compare> maxHeap;
        
        followMap[userId].insert(userId);
        // pushing each followee's last post (latest)
        for (int followeeId : followMap[userId]) {
            if (tweetMap.count(followeeId)) {
                vector<pair<int, int>> tweets = tweetMap[followeeId];
                int index = tweets.size() - 1;
                // pushing time, tweetId, recent index pushed for this followee, followee's id
                maxHeap.push({tweets[index].first, tweets[index].second, followeeId, index});
            }
        }

        while (!maxHeap.empty() && result.size() < 10) {
            vector<int> current = maxHeap.top();
            maxHeap.pop();
            result.push_back(current[1]); // pushing the latest
            int index = current[3];
            if (index > 0) {
                pair<int, int> tweet = tweetMap[current[2]][index - 1];
                maxHeap.push({ tweet.first, tweet.second, current[2], index - 1});
            }
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        followMap[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
};

/*
Final optimization: instead of storing all the tweets just store 10 recent ones for each user -> this improves memory usage, heap operations and time per query
don't push each element from n users and take out 10 like earlier but instead keep the size of the heap 10 -> nlogn = nlog10 = O(n)
O(n), O(N*m + N*M + n)
*/
class Twitter3 {
    int time;
    unordered_map<int, vector<pair<int, int>>> tweetMap;
    unordered_map<int, unordered_set<int>> followMap;
public:
    Twitter3() {
        time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweetMap[userId].push_back({ time, tweetId});
        if (tweetMap[userId].size() > 10) {
            tweetMap[userId].erase(tweetMap[userId].begin());
        }
        time++;
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> result;
        followMap[userId].insert(userId);
        priority_queue<vector<int>, vector<vector<int>>> maxHeap;
        if (followMap[userId].size() >= 10) {
            priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
            // if more than 10 followees for this user - then use minHeap to get the most recent 10 followee's tweets
            for (auto f : followMap[userId]) {
                if (!tweetMap.count(f)) continue;
                int index = tweetMap[f].size() - 1;
                auto &p = tweetMap[f][index];
                pq.push({p.first, p.second, f, index -1 });
                if (pq.size() > 10) pq.pop(); // pop the smallest time - least recent
            }
            while (!pq.empty()) {
                auto t = pq.top();
                pq.pop();
                maxHeap.push({ t[0], t[1], t[2], t[3]});
            }
        } else { // if already less than 10 followees - push all
            for (auto f : followMap[userId]) {
                if (!tweetMap.count(f)) continue;
                int index = tweetMap[f].size() - 1;
                auto &p = tweetMap[f][index];
                maxHeap.push({p.first, p.second, f, index - 1});
            }
        }

        while (!maxHeap.empty() && result.size() < 10) { // most recent to least recent so max timestamp at the top
            vector<int> current = maxHeap.top();
            maxHeap.pop();
            result.push_back(current[1]);
            int index = current[3];
            if (index >= 0) {
                pair<int, int> tweet = tweetMap[current[2]][index];
                maxHeap.push({tweet.first, tweet.second, current[2], index - 1});
            }
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        followMap[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if (followMap[followerId].count(followeeId)) {
            followMap[followerId].erase(followeeId);
        }
    }
};
