import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.util.Iterator;
import java.util.Set;

/**
 * @author Konstantin Bogdanoski (konstantin.b@live.com)
 */
public class CustomReduce extends Reducer<Text, TextWritable, Text, Text> {


    public void reduce(Text key, Iterator<TextWritable> values,
                       Context context) throws IOException, InterruptedException {

        MapWritable map = new MapWritable();
        Text txt = new Text();

        while (values.hasNext()) {
            TextWritable array = values.next();
            Text[] tmpArray = (Text[]) array.toArray();
            for(Text t : tmpArray) {
                if(map.get(t)!= null) {
                    IntWritable val = (IntWritable) map.get(t);
                    map.put(t, new IntWritable(val.get()+1));
                } else {
                    map.put(t, new IntWritable(1));
                }
            }

        }

        Set<Writable> set = map.keySet();
        StringBuffer str = new StringBuffer();
        for(Writable k : set) {

            str.append("key: " + k.toString() + " value: " + map.get(k) + "**");
        }
        txt.set(str.toString());


        context.write(key, txt);
    }
}