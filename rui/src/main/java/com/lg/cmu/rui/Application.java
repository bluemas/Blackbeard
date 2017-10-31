package com.lg.cmu.rui;

import java.awt.EventQueue;

import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;

import com.lg.cmu.rui.ui.MainUI;

@SpringBootApplication
public class Application {

	public static void main(String[] args) {

		ConfigurableApplicationContext context = new SpringApplicationBuilder(Application.class)
				.headless(false)
				.run(args);

		// TODO Windows Look and feel
		EventQueue.invokeLater(new Runnable() {

			@Override
			public void run() {
				MainUI ui = context.getBean(MainUI.class);
				ui.init();
				ui.setVisible(true);
			}
		});
	}
}
