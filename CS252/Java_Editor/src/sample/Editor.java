package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.stage.Stage;

public class Editor extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        primaryStage.setTitle("Java Editor");
        FXMLLoader loader = new FXMLLoader(getClass().getResource("fxml_editor.fxml"));
        loader.setControllerFactory(t->new EditorController(new EditorModel()));
        primaryStage.setScene(new Scene(loader.load()));
        TabPane tabPane=new TabPane();
        Tab tab = new Tab();
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
