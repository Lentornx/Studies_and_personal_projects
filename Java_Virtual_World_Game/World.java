import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;
import java.io.File;
import java.io.IOException;
import java.io.FileWriter;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.*;
import javax.swing.*;
public class World implements ActionListener, KeyListener
{
    public World(int h, int w) throws IOException {
        height = h;
        width = w;
        organisms = new Organism[height*width*2];
        for (int i = 0; i < height * width; i++) {
            organisms[i] = null;
        }
        buttons = new JButton[height][width];
        logs = new String[height*width*2];

        log_area.setEditable(false);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800,800);
        frame.getContentPane().setBackground(new Color(50,50,50));
        frame.setLayout(new BorderLayout());
        frame.setVisible(true);
        frame.addKeyListener(this);

        textfield.setBackground(new Color(225,225,225));
        textfield.setForeground(Color.BLACK);
        textfield.setFont(new Font("Arial",Font.PLAIN,40));
        textfield.setHorizontalAlignment(JLabel.CENTER);
        textfield.setText("Virtual World");
        textfield.setOpaque(true);

        title_panel.setLayout(new BorderLayout());
        title_panel.setBounds(0,0,800,50);

        command_panel.setLayout(new GridLayout(1,4));
        command_panel.setBackground(new Color(150,150,150));
        command_panel.setBounds(0,750,800,50);
        for(int i=0;i<4;i++) {
            cbuttons[i] = new JButton();
            command_panel.add(cbuttons[i]);
            cbuttons[i].setFont(new Font("Arial",Font.PLAIN,10));
            cbuttons[i].setFocusable(false);
            cbuttons[i].addActionListener(this);
        }

        cbuttons[0].setText("end turn");
        cbuttons[1].setText("special");
        cbuttons[2].setText("save");
        cbuttons[3].setText("load");

        add_panel.setLayout(new GridLayout(10,1));
        add_panel.setBackground(new Color(150,150,150));
        add_panel.setBounds(750,0,50,800);
        for(int i=0;i<10;i++) {
            addbuttons[i] = new JButton();
            add_panel.add(addbuttons[i]);
            addbuttons[i].setFont(new Font("Arial",Font.PLAIN,10));
            addbuttons[i].setFocusable(false);
            addbuttons[i].addActionListener(this);
        }

        addbuttons[0].setBackground(Color.WHITE);
        addbuttons[0].setText("S");
        addbuttons[1].setBackground(Color.LIGHT_GRAY);
        addbuttons[1].setText("W");
        addbuttons[2].setBackground(Color.ORANGE);
        addbuttons[2].setText("F");
        addbuttons[3].setBackground(Color.BLUE);
        addbuttons[3].setText("T");
        addbuttons[4].setBackground(Color.RED);
        addbuttons[4].setText("A");
        addbuttons[5].setBackground(Color.GREEN);
        addbuttons[5].setText("G");
        addbuttons[6].setBackground(Color.YELLOW);
        addbuttons[6].setText("D");
        addbuttons[7].setBackground(Color.CYAN);
        addbuttons[7].setText("B");
        addbuttons[8].setBackground(Color.GRAY);
        addbuttons[8].setText("U");
        addbuttons[9].setBackground(Color.DARK_GRAY);
        addbuttons[9].setText("H");

        button_panel.setLayout(new GridLayout(height,width));
        button_panel.setBounds(0,100,800,600);
        button_panel.setBackground(new Color(150,150,150));
        for(int i2=0;i2<width;i2++)
            for(int i=0;i<height;i++) {
                buttons[i2][i] = new JButton();
                button_panel.add(buttons[i2][i]);
                buttons[i2][i].setFont(new Font("Arial",Font.BOLD,9));
                buttons[i2][i].setFocusable(false);
                buttons[i2][i].addActionListener(this);
            }

        title_panel.add(textfield);
        frame.add(title_panel,BorderLayout.NORTH);
        frame.add(button_panel);
        frame.add(command_panel,BorderLayout.SOUTH);
        frame.add(add_panel,BorderLayout.EAST);

        StartGame();
    }

    public int GetH() {
        return height;
    }
    public int GetW() {
        return width;
    }

    public void SetMap(int x, int y, char sign, Color color) {
        buttons[y][x].setBackground(color);
        buttons[y][x].setText(String.valueOf(sign));
    }
    public void AddLog(String log) {
        logs[logCount] = log;
        logCount++;
    }
    public void AddOrganism(Organism newOrganism) {
        if(newOrganism!=null)
        {
            organisms[organismCount] = newOrganism;
            organisms[organismCount].SetOId(organismCount);
            organismCount++;
        }
    }
    public void RmOrganism(int id) {
        if (player == organisms[id])
            player = null;
        Organism tmp =  organisms[id];
        organisms[id] = null;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        for(int i=0;i<width;i++)
            for(int i2=0;i2<height;i2++) {
                if(e.getSource() == buttons[i][i2] && buttons[i][i2].getText() == "" && SpawnSign != null) {
                    PCommand(i2, i, SpawnSign);
                }
            }
        for(int i=0;i<10;i++)
            if(e.getSource()==addbuttons[i])
                SpawnSign = addbuttons[i].getText();

        if(e.getSource()==cbuttons[0]) {
            ResolveTurn();
        }
        if(e.getSource()==cbuttons[1])
            if(player != null && !player.moved && player.GetCd() == 0)
            {
                player.SetCd(10);
                player.SetP(5);
                Print();
            }
        if(e.getSource()==cbuttons[2]) {
            try {
                Save();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
        if(e.getSource()==cbuttons[3]) {
            try {
                Load();
            } catch (FileNotFoundException ex) {
                throw new RuntimeException(ex);
            }
        }
    }
    @Override
    public void keyTyped(KeyEvent e) {}
    @Override
    public void keyPressed(KeyEvent e) {}
    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();

        switch (key)
        {
            case KeyEvent.VK_W:
            case KeyEvent.VK_UP:
                command = 'w';
                ResolveTurn();
                break;

            case KeyEvent.VK_D:
            case KeyEvent.VK_RIGHT:
                command = 'd';
                ResolveTurn();
                break;

            case KeyEvent.VK_S:
            case KeyEvent.VK_DOWN:
                command = 's';
                ResolveTurn();
                break;

            case KeyEvent.VK_A:
            case KeyEvent.VK_LEFT:
                command = 'a';
                ResolveTurn();
                break;

            case KeyEvent.VK_Q:
                if(player != null && player.GetP() > 0) {
                    command = 'q';
                    ResolveTurn();
                }
                break;

            case KeyEvent.VK_E:
                if(player != null && player.GetP() > 0) {
                    command = 'e';
                    ResolveTurn();
                }
                break;

            case KeyEvent.VK_Z:
                if(player != null && player.GetP() > 0) {
                    command = 'z';
                    ResolveTurn();
                }
                break;

            case KeyEvent.VK_C:
                if(player != null && player.GetP() > 0) {
                    command = 'c';
                    ResolveTurn();
                }
                break;

            case KeyEvent.VK_F:
                if(player != null && !player.moved && player.GetCd() == 0)
                {
                    player.SetCd(10);
                    player.SetP(5);
                    Print();
                }
                break;
            case KeyEvent.VK_T:
                ResolveTurn();
                break;
        }
    }
    public void StartGame() {

        player = new Human(width / 2, height / 2, this);
        AddOrganism(player);
        int toBeAdded, rX, rY;
        Random rand = new Random();
        toBeAdded = 1 + (height * width / 60);
        for (int i = 0; i < toBeAdded; i++) {
            for (int i2 = 0; i2 < 15; i2++) {
                while (true) {
                    rX = rand.nextInt(width);
                    rY = rand.nextInt(height);
                    if (LookForCollision(rX, rY) == null) {
                        if(i2 < 3)
                            organisms[organismCount] = new Sheep(rX, rY, this);
                        else if (i2 < 4)
                            organisms[organismCount] = new Wolf(rX, rY, this);
                        else if (i2 < 6)
                            organisms[organismCount] = new Fox(rX, rY, this);
                        else if (i2 < 8)
                            organisms[organismCount] = new Turtle(rX, rY, this);
                        else if (i2 < 10)
                            organisms[organismCount] = new Antelope(rX, rY, this);
                        else if (i2 < 11)
                            organisms[organismCount] = new Grass(rX, rY, this);
                        else if (i2 < 12)
                            organisms[organismCount] = new Guarana(rX, rY, this);
                        else if (i2 < 13)
                            organisms[organismCount] = new Dandelion(rX, rY, this);
                        else if (i2 < 14)
                            organisms[organismCount] = new Wolfberry(rX, rY, this);
                        else
                            organisms[organismCount] = new Hogweed(rX, rY, this);
                        organismCount++;
                        break;
                    }
                }
            }
        }
        sort();
        ResolveTurn();
    }

    private void sort() {
        int tmp = organismCount;
        for (int i = 0; i < tmp; i++)
        {
            if (organisms[i] == null)
            {
                for (int i2 = tmp - 1; i2 > i; i2--)
                {
                    if (organisms[i2] != null)
                    {
                        organisms[i] = organisms[i2];
                        organisms[i2] = null;
                        break;
                    }
                }
            }
        }

        for (tmp = 0; organisms[tmp] != null; tmp++) {}
        organismCount = tmp;

        for (int i = organismCount - 1; i > 0; i--) {
            for (int i2 = organismCount - 1; i2 > organismCount - 1 -i; i2--)
            {
                if (organisms[i2].GetI() > organisms[i2 - 1].GetI()) {
                    Organism swapTmp = organisms[i2];
                    organisms[i2] = organisms[i2 - 1];
                    organisms[i2 - 1] = swapTmp;
                }
                else if (organisms[i2].GetI() == organisms[i2 - 1].GetI())
                {
                    if (organisms[i2].GetAge() > organisms[i2 - 1].GetAge())
                    {
                        Organism swapTmp = organisms[i2];
                        organisms[i2] = organisms[i2 - 1];
                        organisms[i2 - 1] = swapTmp;
                    }
                }
            }
        }

        for (int i = 0; i < organismCount; i++)
            organisms[i].SetOId(i);
    }

    Organism LookForCollision(int x, int y) {
        for (int i = 0; i < organismCount; i++) {
            if(organisms[i] != null)
                if (organisms[i].GetX() == x && organisms[i].GetY() == y)
                    return organisms[i];
        }
        return null;
    }

    void ResolveTurn() {
        for (int i = 0; i<logCount; i++)
            logs[i] = "";
        logCount = 0;
        for (int i = 0; i < organismCount; i++) {
            if (organisms[i] != null && !organisms[i].HasMoved())
            {
                if (organisms[i] == player)
                {
                    player.SetAction(command);
                    player.TakeAction();
                }
                else
                {
                    organisms[i].TakeAction();
                }
            }
        }
        sort();
            for (int i = 0; i < organismCount; i++) {
                if (organisms[i].GetAge() == 0) {
                    organisms[i].SetAge(1);
                }
                organisms[i].SetHasMoved(false);
            }
            Print();

        JFrame log_frame = new JFrame("logs");
        JScrollPane log_pane = new JScrollPane(log_area);
        log_frame.add(log_pane);
        log_frame.pack();
        log_frame.setVisible(true);

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void Save() throws IOException {
        String name = JOptionPane.showInputDialog("please name savefile");
        File file = new File(name);
        FileWriter Writer = new FileWriter(file);
        Writer.write(width + " " + height + '\n');
        count = 0;
        for (int i = 0; i < organismCount; i++)
        {
            if (organisms[i] != null)
                count++;
        }
        Writer.write(count + "" + '\n');
        for (int i = 0; i < organismCount; i++)
        {
            if (organisms[i] != null)
            {
                Writer.write(organisms[i].GetSId() + " " + organisms[i].GetS() + " " + organisms[i].GetI() + " " + organisms[i].GetX() + " "
                        + organisms[i].GetY() + " " + organisms[i].GetAge() + " " + organisms[i].GetOId() + " " + organisms[i].HasMoved() + '\n');
            }
        }
        if(player != null)
            Writer.write(player.GetCd() + " " + player.GetP());
        Writer.close();
    }

    private void Load() throws FileNotFoundException {
        String name = JOptionPane.showInputDialog("please name savefile to load");
        File file = new File(name);
        Scanner cin = new Scanner(file);
        width = cin.nextInt();
        height = cin.nextInt();
        organisms = new Organism[height * width];
        for (int i = 0; i < height * width; i++) {
            organisms[i] = null;
        }
        map = new char [height][width];
        organismCount = cin.nextInt();;
        int species, str, ini, x, y, age, oId; boolean moved;
        for (int i = 0; i < organismCount; i++)
        {
            species = cin.nextInt();
            str = cin.nextInt();
            ini = cin.nextInt();
            x = cin.nextInt();
            y = cin.nextInt();
            age = cin.nextInt();
            oId = cin.nextInt();
            moved = cin.nextBoolean();
            if (species == 1)
                organisms[i] = new Sheep(str, ini, x, y, age, oId, moved, this);
            else if (species == 2)
                organisms[i] = new Wolf(str, ini, x, y, age, oId, moved, this);
            else if (species == 3)
                organisms[i] = new Fox(str, ini, x, y, age, oId, moved, this);
            else if (species == 4)
                organisms[i] = new Turtle(str, ini, x, y, age, oId, moved, this);
            else if (species == 5)
                organisms[i] = new Antelope(str, ini, x, y, age, oId, moved, this);
            else if (species == 6)
                organisms[i] = new Grass(str, ini, x, y, age, oId, moved, this);
            else if (species == 7)
                organisms[i] = new Guarana(str, ini, x, y, age, oId, moved, this);
            else if (species == 8)
                organisms[i] = new Dandelion(str, ini, x, y, age, oId, moved, this);
            else if (species == 9)
                organisms[i] = new Wolfberry(str, ini, x, y, age, oId, moved, this);
            else if (species == 10)
                organisms[i] = new Hogweed(str, ini, x, y, age, oId, moved, this);
            else
            {
                organisms[i] = new Human(str, ini, x, y, age, oId, moved, this);
                player = (Human)organisms[i];
            }
        }
        int cd, p;
        if(player != null){
            cd = cin.nextInt();
            p = cin.nextInt();
            player.SetCd(cd);
            player.SetP(p);
        }
        Print();
    }

    public void Print() {
        for (int i = 0; i < width; i++)
            for (int i2 = 0; i2 < height; i2++) {
                buttons[i2][i].setBackground(new Color(150, 150, 150));
                buttons[i2][i].setText("");
            }
        for (int i = 0; i < organismCount; i++)
            if(organisms[i] != null)
                organisms[i].Print();
        if(player != null){
            if (player.GetP() > 0)
                cbuttons[1].setText("active " + player.GetP());
            else if (player.GetCd() > 0)
                cbuttons[1].setText("cooldown " + player.GetCd());
            else
                cbuttons[1].setText("special");
        }
        else cbuttons[1].setText("");

        for (int i = 0; i<logCount; i++)
            if(logs[i] != " ")
                log_area.append(logs[i]);
    }

    public void PCommand(int x, int y, String s)
    {
        Print();
        if(s == "S")
            organisms[organismCount] = new Sheep(x, y, this);
        else if (s == "W")
            organisms[organismCount] = new Wolf(x, y, this);
        else if (s == "F")
            organisms[organismCount] = new Fox(x, y, this);
        else if (s == "T")
            organisms[organismCount] = new Turtle(x, y, this);
        else if (s == "A")
            organisms[organismCount] = new Antelope(x, y, this);
        else if (s == "G")
            organisms[organismCount] = new Grass(x, y, this);
        else if (s == "U")
            organisms[organismCount] = new Guarana(x, y, this);
        else if (s == "D")
            organisms[organismCount] = new Dandelion(x, y, this);
        else if (s == "B")
            organisms[organismCount] = new Wolfberry(x, y, this);
        else
            organisms[organismCount] = new Hogweed(x, y, this);
        organismCount++;
        sort();
        Print();
    }
    private int height, width, count;
    private int organismCount = 0, logCount = 0;
    private char[][] map;
    private char command;
    private Organism[] organisms;
    private Human player;
    private String SpawnSign;
    private JFrame frame = new JFrame();
    private JPanel title_panel = new JPanel();
    private JPanel button_panel = new JPanel();
    private JPanel command_panel = new JPanel();
    private JTextArea log_area = new JTextArea(10,50);
    private JPanel add_panel = new JPanel();
    private JLabel textfield = new JLabel();
    private JButton[][] buttons;
    private JButton[] cbuttons = new JButton[4];
    private JButton[] addbuttons = new JButton[10];
    private String[] logs;
};