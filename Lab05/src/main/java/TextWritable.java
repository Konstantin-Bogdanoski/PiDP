import org.apache.hadoop.io.ArrayWritable;
import org.apache.hadoop.io.Text;

/**
 * @author Konstantin Bogdanoski (konstantin.b@live.com)
 */
public class TextWritable extends ArrayWritable {
    public TextWritable() {
        super(Text.class);
    }
}