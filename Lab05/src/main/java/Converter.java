import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.*;

import java.util.Map;


/**
 * @author Konstantin Bogdanoski (konstantin.b@live.com)
 */
public class Converter {

        private String mapToString(Map<String, Integer> map) {
            StringBuilder sb = new StringBuilder();
            String delimiter = ", ";
            for (Map.Entry<String, Integer> entry : map.entrySet()) {
                sb.append(
                        String.format("%s:%d", entry.getKey(), entry.getValue())
                ).append(delimiter);
            }
            sb.setLength(sb.length()-delimiter.length());
            return sb.toString();
        }

        public static void main(String[] args) throws Exception {
            JobConf conf = new JobConf(Converter.class);
            conf.setJobName("Convert");

            conf.setOutputKeyClass(Text.class);
            conf.setOutputValueClass(IntWritable.class);

            conf.setMapperClass(CustomMap.class);
            conf.setCombinerClass(CustomReduce.class);
            conf.setReducerClass(CustomReduce.class);

            conf.setInputFormat(TextInputFormat.class);
            conf.setOutputFormat(TextOutputFormat.class);

            FileInputFormat.setInputPaths(conf, new Path(args[0]));
            FileOutputFormat.setOutputPath(conf, new Path(args[1]));

            JobClient.runJob(conf);
        }
    }
}
