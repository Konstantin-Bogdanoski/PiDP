import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;

/**
 * @author Konstantin Bogdanoski (konstantin.b@live.com)
 */
class CustomMap extends Mapper<LongWritable, Text, Text, Text> {

    private final Text key = new Text();
    private final Text output = new Text();

    @Override
    protected void map(LongWritable offset, Text value, Context context) throws IOException, InterruptedException {

        int separatorIndex = value.find(",");

        final String valueStr = value.toString();
        if (separatorIndex < 0) {
            System.err.printf("mapper: not enough records for %s", valueStr);
            return;
        }
        String dateKey = valueStr.substring(0, separatorIndex).trim();
        String tokens = valueStr.substring(1 + separatorIndex).trim().replaceAll("\\p{Space}", "");

        SimpleDateFormat fmtFrom = new SimpleDateFormat("yyyy-MM-dd");
        SimpleDateFormat fmtTo = new SimpleDateFormat("yyyy-MM");

        try {
            dateKey = fmtTo.format(fmtFrom.parse(dateKey));
            key.set(dateKey);
        } catch (ParseException ex) {
            System.err.printf("mapper: invalid key format %s", dateKey);
            return;
        }

        output.set(tokens);
        context.write(key, output);
    }
}
