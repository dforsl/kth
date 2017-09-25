package database;

import java.util.List;

import twitter4j.Query;
import twitter4j.QueryResult;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.conf.ConfigurationBuilder;
import utils.Logger;

public class TwitterClient {
	private Twitter twitter;	
	
	public TwitterClient() {
		init();
	}
	
	private void init() {
		ConfigurationBuilder cb = new ConfigurationBuilder();
		cb.setDebugEnabled(true)
		  .setOAuthConsumerKey("cAYxQQ7IGScvHIpXZMnYQ")
		  .setOAuthConsumerSecret("UUadkkKlR9dLtWeGWzPvdh2ltJmukQW6LULPS0YZCVE")
		  .setOAuthAccessToken("1304242686-xysSpdln3aRZTmQ44YjiXkHGRiFeiIx3dmK0nsK")
		  .setOAuthAccessTokenSecret("7OKteJ94DRYFrdqwek7upmCRSsurv7JxJ0WAHm1mfac");
		
		TwitterFactory factory = new TwitterFactory(cb.build());
		twitter = factory.getInstance();
	}
	
	public QueryResult search(List<String> params) {
		
		String queryString = new String();
		for(String p : params) {
			queryString += " " + p;
		}
		
		Logger.logMessage("Twitter search for: " + queryString.trim());
		Query q = new Query("exclude:retweets " + queryString.trim());
		q.lang("en");
		q.setCount(100);
		try {
			return twitter.search(q);
		} catch (TwitterException e) {
			Logger.logError("Twitter Error", e);
			return null;
		}
	}
}
