package sample;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.List;

public class EditorModel {
    public void close(){
        System.exit(0);
    }
    public void save(TextFile textFile){
        try {
            Files.write(textFile.getFile(),textFile.getContent(), StandardOpenOption.CREATE);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public IOResult<TextFile> load(Path file){
        try {
            List<String> content = Files.readAllLines(file);
            return new IOResult<>(true,new TextFile(file,content));
        } catch (IOException e) {
            e.printStackTrace();
            return new IOResult<>(false, null);
        }
    }
}
