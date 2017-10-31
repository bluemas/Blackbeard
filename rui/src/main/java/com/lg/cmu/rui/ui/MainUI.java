package com.lg.cmu.rui.ui;

import java.awt.Container;
import java.awt.event.ActionEvent;

import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import org.springframework.stereotype.Component;

@Component
public class MainUI extends JFrame {

	private static final long serialVersionUID = 2243993209583521628L;

	public void init() {
		setLookAndFeel();
		initComponent();
		setFrameUp();
	}

	private void setLookAndFeel() {
		try {
			UIManager.setLookAndFeel(
					UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
	}

	private void setFrameUp() {
		setTitle("Quit button");
        setSize(1600, 900);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	private void initComponent() {
		JLabel Image = new JLabel();


        Container pane = getContentPane();
        GroupLayout gl = new GroupLayout(pane);
        pane.setLayout(gl);

        gl.setAutoCreateContainerGaps(true);

		JButton quitButton = new JButton("Quit");

        quitButton.addActionListener((ActionEvent event) -> {
            System.exit(0);
        });

        gl.setHorizontalGroup(gl.createSequentialGroup()
                .addComponent(quitButton)
        );

        gl.setVerticalGroup(gl.createSequentialGroup()
                .addComponent(quitButton)
        );
	}

}
