package rui;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.wb.swt.SWTResourceManager;

import rui.monitor.CameraImageReceiver;
import rui.monitor.NetworkManager;
import rui.utils.Utils;

public class RUIMain {
	protected Shell shlBlackbeardPirates;
	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());
	private Label cameraImage;
	public static Display display;

	private Text txtLogMessge;
	private CameraImageReceiver imageReceiver;
	private NetworkManager networkManager;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			RUIMain window = new RUIMain();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Open the window.
	 */
	public void open() {
		display = Display.getDefault();
		createContents();

		shlBlackbeardPirates.open();
		shlBlackbeardPirates.layout();

		imageReceiver = new CameraImageReceiver(this);
		new Thread(imageReceiver).start();

		networkManager = new NetworkManager(this);

		shlBlackbeardPirates.addListener(SWT.Close, new Listener() {
			public void handleEvent(Event event) {
				if (imageReceiver != null) {
					imageReceiver.close();
				}
				
				if (networkManager != null) {
					networkManager.disconnect();
				}
			}
		});

		while (!shlBlackbeardPirates.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shlBlackbeardPirates = new Shell();
		shlBlackbeardPirates.setSize(1104, 700);
		shlBlackbeardPirates.setText("Blackbeard Pirates");
		shlBlackbeardPirates.setLayout(new GridLayout(1, false));

		Composite composite = new Composite(shlBlackbeardPirates, SWT.NONE);
		composite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		composite.setLayout(new GridLayout(4, false));

		Group grpRemoteSetup = new Group(composite, SWT.NONE);
		grpRemoteSetup.setLayout(new GridLayout(1, false));
		grpRemoteSetup.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		grpRemoteSetup.setText("Remote Setup");
		formToolkit.adapt(grpRemoteSetup);
		formToolkit.paintBordersFor(grpRemoteSetup);

		Button btnConnect = new Button(grpRemoteSetup, SWT.FLAT);
		btnConnect.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.connect();
			}
		});

		GridData gd_btnConnect = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnConnect.heightHint = 32;
		btnConnect.setLayoutData(gd_btnConnect);
		formToolkit.adapt(btnConnect, true, true);
		btnConnect.setText("Connect To Robot");

		Button btnInitialize = new Button(grpRemoteSetup, SWT.FLAT | SWT.CENTER);
		btnInitialize.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.sendCommand(new Command("1", ""));
			}
		});
		GridData gd_btnInitialize = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnInitialize.heightHint = 32;
		btnInitialize.setLayoutData(gd_btnInitialize);
		btnInitialize.setText("Robot Initialization");
		formToolkit.adapt(btnInitialize, true, true);

		Group grpCameraView = new Group(composite, SWT.NONE);
		grpCameraView.setLayout(new FillLayout(SWT.HORIZONTAL));
		GridData gd_grpCameraView = new GridData(SWT.LEFT, SWT.FILL, false, false, 1, 2);
		gd_grpCameraView.heightHint = 256;
		gd_grpCameraView.widthHint = 256;
		grpCameraView.setLayoutData(gd_grpCameraView);
		grpCameraView.setText("Camera View");
		formToolkit.adapt(grpCameraView);
		formToolkit.paintBordersFor(grpCameraView);

		Composite compositeCamera = new Composite(grpCameraView, SWT.NONE);
		formToolkit.adapt(compositeCamera);
		formToolkit.paintBordersFor(compositeCamera);
		compositeCamera.setLayout(new FillLayout(SWT.HORIZONTAL));

		cameraImage = new Label(compositeCamera, SWT.NONE);
		formToolkit.adapt(cameraImage, true, true);

		Group grpRobotMovement = new Group(composite, SWT.NONE);
		grpRobotMovement.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		GridLayout gl_grpRobotMovement = new GridLayout(3, false);
		grpRobotMovement.setLayout(gl_grpRobotMovement);
		grpRobotMovement.setText("Robot Movement");
		formToolkit.adapt(grpRobotMovement);
		formToolkit.paintBordersFor(grpRobotMovement);

		new Label(grpRobotMovement, SWT.NONE);

		Button btnUp = new Button(grpRobotMovement, SWT.FLAT | SWT.CENTER);
		btnUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "F"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "S"));
			}
		});
		btnUp.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, true, true, 1, 1));
		btnUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-up-01_186407.png"));
		new Label(grpRobotMovement, SWT.NONE);

		Button btnLeft = new Button(grpRobotMovement, SWT.FLAT);
		btnLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "L"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "S"));
			}
		});
		btnLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-left-01_186410.png"));
		new Label(grpRobotMovement, SWT.NONE);

		Button btnRight = new Button(grpRobotMovement, SWT.FLAT);
		btnRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "R"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "S"));
			}
		});
		btnRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-right-01_186409.png"));
		new Label(grpRobotMovement, SWT.NONE);

		Button btnDown = new Button(grpRobotMovement, SWT.FLAT | SWT.CENTER);
		btnDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "B"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("3", "S"));
			}
		});
		btnDown.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-down-01_186411.png"));
		new Label(grpRobotMovement, SWT.NONE);
		new Label(grpRobotMovement, SWT.NONE);
		new Label(grpRobotMovement, SWT.NONE);
		new Label(grpRobotMovement, SWT.NONE);

		Group grpMapView = new Group(composite, SWT.NONE);
		grpMapView.setLayout(new FillLayout(SWT.HORIZONTAL));
		GridData gd_grpMapView = new GridData(SWT.FILL, SWT.FILL, true, false, 1, 3);
		gd_grpMapView.widthHint = 256;
		grpMapView.setLayoutData(gd_grpMapView);
		grpMapView.setText("Map View");
		formToolkit.adapt(grpMapView);
		formToolkit.paintBordersFor(grpMapView);

		Composite compositeMap = new Composite(grpMapView, SWT.NONE);
		formToolkit.adapt(compositeMap);
		formToolkit.paintBordersFor(compositeMap);

		Group grpMode = new Group(composite, SWT.NONE);
		grpMode.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		grpMode.setText("Mode Selection");
		formToolkit.adapt(grpMode);
		formToolkit.paintBordersFor(grpMode);

		RowLayout rl_grpMode = new RowLayout(SWT.VERTICAL);
		rl_grpMode.center = true;
		rl_grpMode.justify = true;
		rl_grpMode.fill = true;
		grpMode.setLayout(rl_grpMode);

		Button btnAuto = new Button(grpMode, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnAuto.setLayoutData(new RowData(SWT.DEFAULT, 32));
		btnAuto.setText("Autonomous");

		Button btnManual = new Button(grpMode, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnManual.setLayoutData(new RowData(SWT.DEFAULT, 32));
		btnManual.setText("Manual");

		Button btnSuspend = new Button(grpMode, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnSuspend.setLayoutData(new RowData(164, 32));
		btnSuspend.setText("Suspend");

		Group grpPanTilt = new Group(composite, SWT.NONE);
		grpPanTilt.setLayout(new GridLayout(3, false));
		grpPanTilt.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		grpPanTilt.setText("Camera Pan/Tilt");
		formToolkit.adapt(grpPanTilt);
		formToolkit.paintBordersFor(grpPanTilt);
		new Label(grpPanTilt, SWT.NONE);

		Button btnCameraUp = new Button(grpPanTilt, SWT.FLAT);
		btnCameraUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "U"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "S"));
			}
		});
		btnCameraUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_up_alt1_118743.png"));
		formToolkit.adapt(btnCameraUp, true, true);
		new Label(grpPanTilt, SWT.NONE);

		Button btnCameraLeft = new Button(grpPanTilt, SWT.FLAT);
		btnCameraLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "L"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "S"));
			}
		});
		btnCameraLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_left_alt1_118748.png"));
		formToolkit.adapt(btnCameraLeft, true, true);
		new Label(grpPanTilt, SWT.NONE);

		Button btnCameraRight = new Button(grpPanTilt, SWT.FLAT);
		btnCameraRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "R"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "S"));
			}
		});
		btnCameraRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_right_alt1_118746.png"));
		formToolkit.adapt(btnCameraRight, true, true);
		new Label(grpPanTilt, SWT.NONE);

		Button btnCameraDown = new Button(grpPanTilt, SWT.FLAT);
		btnCameraDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "D"));
			}
			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command("4", "S"));
			}
		});
		btnCameraDown.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_down_alt1_118751.png"));
		formToolkit.adapt(btnCameraDown, true, true);
		new Label(grpPanTilt, SWT.NONE);

		Group grpMonitoringInfo = new Group(composite, SWT.NONE);
		grpMonitoringInfo.setLayout(new GridLayout(5, false));
		grpMonitoringInfo.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 3, 1));
		grpMonitoringInfo.setText("Monitoring Information");
		formToolkit.adapt(grpMonitoringInfo);
		formToolkit.paintBordersFor(grpMonitoringInfo);

		Composite compositeStatus = new Composite(grpMonitoringInfo, SWT.NONE);
		compositeStatus.setFont(SWTResourceManager.getFont("Courier", 11, SWT.BOLD));
		compositeStatus.setBackground(SWTResourceManager.getColor(SWT.COLOR_TRANSPARENT));
		compositeStatus.setLayout(new GridLayout(8, false));
		GridData gd_compositeStatus = new GridData(SWT.FILL, SWT.CENTER, true, false, 5, 1);
		gd_compositeStatus.heightHint = 25;
		compositeStatus.setLayoutData(gd_compositeStatus);
		formToolkit.adapt(compositeStatus);
		formToolkit.paintBordersFor(compositeStatus);

		Label lblNetworkStatus = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblNetworkStatus, true, true);
		lblNetworkStatus.setText("Network Status :");

		Label lblConnected = new Label(compositeStatus, SWT.NONE);
		GridData gd_lblConnected = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_lblConnected.widthHint = 82;
		lblConnected.setLayoutData(gd_lblConnected);
		formToolkit.adapt(lblConnected, true, true);
		lblConnected.setText("Connected");

		Label split0 = new Label(compositeStatus, SWT.SEPARATOR | SWT.VERTICAL);
		GridData gd_split0 = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_split0.heightHint = 10;
		split0.setLayoutData(gd_split0);
		formToolkit.adapt(split0, true, true);

		Label lblTimeElapsed = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblTimeElapsed, true, true);
		lblTimeElapsed.setText("Time Elapsed :");

		Label lblTime = new Label(compositeStatus, SWT.NONE);
		GridData gd_lblTime = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_lblTime.widthHint = 60;
		lblTime.setLayoutData(gd_lblTime);
		formToolkit.adapt(lblTime, true, true);
		lblTime.setText("45s");

		Label split1 = new Label(compositeStatus, SWT.SEPARATOR | SWT.VERTICAL);
		GridData gd_split1 = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_split1.heightHint = 10;
		split1.setLayoutData(gd_split1);
		formToolkit.adapt(split1, true, true);

		Label lblRobotStatus = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblRobotStatus, true, true);
		lblRobotStatus.setText("Robot Status :");

		Label lblRobotMessage = new Label(compositeStatus, SWT.NONE);
		lblRobotMessage.setForeground(SWTResourceManager.getColor(SWT.COLOR_RED));
		lblRobotMessage.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(lblRobotMessage, true, true);
		lblRobotMessage.setText("WARNING COLLISION");
		new Label(grpMonitoringInfo, SWT.NONE);
		new Label(grpMonitoringInfo, SWT.NONE);
		new Label(grpMonitoringInfo, SWT.NONE);
		new Label(grpMonitoringInfo, SWT.NONE);
		new Label(grpMonitoringInfo, SWT.NONE);

		Group grpDistanceLeft = new Group(grpMonitoringInfo, SWT.NONE);
		GridData gd_grpDistanceLeft = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceLeft.widthHint = 170;
		grpDistanceLeft.setLayoutData(gd_grpDistanceLeft);
		grpDistanceLeft.setLayout(new GridLayout(1, false));
		grpDistanceLeft.setText("Left Distance");
		formToolkit.adapt(grpDistanceLeft);
		formToolkit.paintBordersFor(grpDistanceLeft);

		Label lblLeftDistance = new Label(grpDistanceLeft, SWT.NONE);
		lblLeftDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblLeftDistance.setFont(SWTResourceManager.getFont("Courier", 26, SWT.BOLD));
		formToolkit.adapt(lblLeftDistance, true, true);
		lblLeftDistance.setText("100 mm");
		new Label(grpMonitoringInfo, SWT.NONE);

		Group grpDistanceFront = new Group(grpMonitoringInfo, SWT.NONE);
		grpDistanceFront.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		grpDistanceFront.setLayout(new GridLayout(1, false));
		grpDistanceFront.setText("Front Distance");
		formToolkit.adapt(grpDistanceFront);
		formToolkit.paintBordersFor(grpDistanceFront);

		Label lblFrontDistance = new Label(grpDistanceFront, SWT.NONE);
		lblFrontDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblFrontDistance.setText("100 mm");
		lblFrontDistance.setFont(SWTResourceManager.getFont("Courier", 26, SWT.BOLD));
		lblFrontDistance.setBounds(0, 0, 155, 37);
		formToolkit.adapt(lblFrontDistance, true, true);
		new Label(grpMonitoringInfo, SWT.NONE);

		Group grpDistanceRight = new Group(grpMonitoringInfo, SWT.NONE);
		GridData gd_grpDistanceRight = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceRight.widthHint = 170;
		grpDistanceRight.setLayoutData(gd_grpDistanceRight);
		grpDistanceRight.setLayout(new GridLayout(1, false));
		grpDistanceRight.setText("Right Distance");
		formToolkit.adapt(grpDistanceRight);
		formToolkit.paintBordersFor(grpDistanceRight);

		Label lblRightDistance = new Label(grpDistanceRight, SWT.NONE);
		lblRightDistance.setBackground(SWTResourceManager.getColor(SWT.COLOR_TRANSPARENT));
		lblRightDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblRightDistance.setFont(SWTResourceManager.getFont("Courier", 26, SWT.BOLD));
		formToolkit.adapt(lblRightDistance, true, true);
		lblRightDistance.setText("100 mm");

		Group grpConsole = new Group(composite, SWT.NONE);
		grpConsole.setLayout(new GridLayout(1, false));
		GridData gd_grpConsole = new GridData(SWT.FILL, SWT.FILL, true, true, 4, 1);
		gd_grpConsole.heightHint = 102;
		grpConsole.setLayoutData(gd_grpConsole);
		grpConsole.setText("Log Console");
		formToolkit.adapt(grpConsole);
		formToolkit.paintBordersFor(grpConsole);

		txtLogMessge = new Text(grpConsole, SWT.BORDER | SWT.READ_ONLY | SWT.WRAP | SWT.V_SCROLL | SWT.MULTI);
		txtLogMessge.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.adapt(txtLogMessge, true, true);
	}

	public Label getCameraImageLabel() {
		return this.cameraImage;
	}
	
	public void appendLogMessage(String message) {
		display.asyncExec(new Runnable() {
			public void run() {
				try {
					txtLogMessge.append(String.format("[%s] %s \n", Utils.getLogTime(), message));
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public void notify(String message) {
		appendLogMessage(message);
	}
}
