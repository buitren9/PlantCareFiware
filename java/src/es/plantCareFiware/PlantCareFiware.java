package es.plantCareFiware;
import java.util.HashMap;
import upm_grove.GroveRelay;
import upm_i2clcd.Jhd1313m1;
import mraa.Platform;
import mraa.mraa;

public class PlantCareFiware {
	


  public static void main(String[] args) {

	  Platform platform = mraa.getPlatformType();
	  
	  //check the platform type
      if (platform != Platform.INTEL_GALILEO_GEN1 &&
              platform != Platform.INTEL_GALILEO_GEN2 &&
              platform != Platform.INTEL_EDISON_FAB_C) {
          System.err.println("Unsupported platform, exiting");
          return;
      }
      upm_grove.GroveRelay relay = new GroveRelay(4); 
      upm_i2clcd.Jhd1313m1 lcd = new upm_i2clcd.Jhd1313m1(1, 0x3E, 0x62);
      
     
     

      
      while (true) {
    	  
    	  lcd.clear();
    	  HashMap<String, String> measures = new HashMap<>();
    	  lcd.setCursor(0,0);
    	  String value = String.valueOf(MySensors.loadHumidity(1));
    	  measures = addDataToSend("h", value, measures);
    	  lcd.write("Humidity "+value);
    	  
    	  value = String.valueOf(MySensors.loadTemperature(0));
    	  measures = addDataToSend("t", value, measures);
    	
          lcd.setCursor(1,0);
          lcd.write("Temperature "+value);
          
          value = isWet(MySensors.loadHumidity(1), relay, lcd);
          measures = addDataToSend("r", value, measures);
          
    	  FiwareConnector.postMeasures(measures);
    	  
    	  try {
			Thread.sleep(50000);
		} catch (InterruptedException e) {
			
			e.printStackTrace();
		}
      }
	  	  
  }
  
  /**
   * Add data to the Hashmap
   * @param key
   * @param value
   * @param measures
   * @return
   */
  public static  HashMap<String, String> addDataToSend(String key, String value, HashMap<String,String> measures) {
	 HashMap<String, String> measuresOutput = new HashMap<>(measures);
	 measuresOutput.put(key, value);
	return measuresOutput;  
  }
  
  /**
   * Check the humidity with a moisture sensor and turn on/off a relay, it prints in a LCD the status of the relay
   * @param humidity
   * @param relay
   * @param myLCD
   * @return
   */
  public static String isWet(float humidity, GroveRelay relay,Jhd1313m1 myLCD ){
	  
		if (humidity < 40){
			relay.on();
			myLCD.write("Pump: On");
			return "1";
		}else{
			relay.off();
			myLCD.write("Pump: Off");
			return "0";
		}

	  
  }
   

}