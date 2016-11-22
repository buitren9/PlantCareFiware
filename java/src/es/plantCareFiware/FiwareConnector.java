package es.plantCareFiware;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

import com.mashape.unirest.http.exceptions.UnirestException;

/**
 * This connector allows to upload the data to the fi-ware iot agent using UL2.0
 * @author @franbuipa
 *
 */
public class FiwareConnector {
	
	private static String URL_SERVICE = "YOUR_SERVER";
	private static String PORT = "xxxx";
	private static String DEVICE_NAME = "myManualDevice";
	private static String API_KEY ="YOUR_API_KEY";
	
	/**
	 * Post the data to a Fiware service
	 * @param measures it is a HasMap where the key is the identifier of the attribute example key="T" value "24"
	 */
	public static void postMeasures (HashMap<String, String>measures){
		
		String body = new String("");
		Set<Entry<String, String>> set = measures.entrySet();
		
		Iterator<Entry<String, String>> i = set.iterator();
		
		while (i.hasNext()){
			try {
				Map.Entry<String, String> element = (Map.Entry<String,String>)i.next();
				if (!body.equalsIgnoreCase("")){
					body = body.concat("#");
				}
				
				body = body.concat(element.getKey());
				body = body.concat("|");
				body = body.concat(element.getValue());
				sendData(body);
				
			} catch (Exception e) {
				System.out.println("Error uploading data");
				System.out.println(e);
				
			}
			
		}
		
	}
	
	/**
	 * Send Data using OkHttp library 
	 * @param data String with the data that is going to be send
	 * @throws IOException
	 * @throws UnirestException
	 */
	public static void sendData( String data) throws IOException, UnirestException{
	
		OkHttpClient client = new OkHttpClient();

		MediaType mediaType = MediaType.parse("text/plain");
		RequestBody body = RequestBody.create(mediaType, data);
		Request request = new Request.Builder()
		  .url("http://"+URL_SERVICE+":"+PORT+"/iot/d?i="+DEVICE_NAME+"&k="+API_KEY)
		  .post(body)
		  .build();
		
		System.out.println(data);
		System.out.println(request.url());
		Response response = client.newCall(request).execute();
		
		if (response.isSuccessful()){
			System.out.println("Data Uploaded to Fi-Ware Stack");
		}else{
			System.out.println(String.format("Error Status Code:%s",response.message()));
		}
		
	}

}
