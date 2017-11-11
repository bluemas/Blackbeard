package rui;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CLabel;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.wb.swt.SWTResourceManager;

import rui.configure.ConfigManager;
import rui.maze.MazeDrawer;
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
	private Canvas canvas;
	private MazeDrawer mazeDrawer;

	private Button btnUp;
	private Button btnRight;
	private Button btnDown;
	private Button btnLeft;

	private Button btnCameraUp;
	private Button btnCameraLeft;
	private Button btnCameraRight;
	private Button btnCameraDown;

	private Label lblLeftDistance;
	private Label lblFrontDistance;
	private Label lblRightDistance;

	private Button btnAuto;
	private Button btnManual;
	private CLabel lblSuspended;

	private Label lblConnected;
	private Label lblRobotMessage;
	private Label lblTime;
	private Text txtIP;
	private Text txtPort;
	private Text txtListenPort;
	private Text txtRowCnt;
	private Text txtColumnCnt;
	private Text txtMaxPacketSize;
	private Text txtCommandMessages;

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
		mazeDrawer = new MazeDrawer(this);

		setEnableRobotMovement(false);
		setNetworkStatus(false);
		setConfigData();

		shlBlackbeardPirates.addListener(SWT.Close, new Listener() {
			public void handleEvent(Event event) {
				if (imageReceiver != null) {
					imageReceiver.close();
				}

				if (networkManager != null) {
					networkManager.disconnect();
				}

				SWTResourceManager.dispose();
			}
		});

		while (!shlBlackbeardPirates.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	private void setConfigData() {
		ConfigManager configManager = ConfigManager.getInstance();

		this.txtIP.setText(configManager.getRobotIp());
		this.txtPort.setText(configManager.getRobotPort() + "");
		this.txtListenPort.setText(configManager.getCameraListenport() + "");
		this.txtMaxPacketSize.setText(configManager.getCameraDatagramMaxSize() + "");
		this.txtRowCnt.setText(configManager.getMazeRowCount() + "");
		this.txtColumnCnt.setText(configManager.getMazeColumnCount() + "");
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shlBlackbeardPirates = new Shell();
		shlBlackbeardPirates.setSize(1400, 750);
		shlBlackbeardPirates.setText("Blackbeard Pirates");
		shlBlackbeardPirates.setLayout(new GridLayout(1, false));

		Composite composite = new Composite(shlBlackbeardPirates, SWT.NONE);
		composite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		composite.setLayout(new GridLayout(4, false));

		Group grpRemoteSetup = new Group(composite, SWT.NONE);
		grpRemoteSetup.setLayout(new GridLayout(1, false));
		GridData gd_grpRemoteSetup = new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1);
		gd_grpRemoteSetup.widthHint = 150;
		grpRemoteSetup.setLayoutData(gd_grpRemoteSetup);
		grpRemoteSetup.setText("Remote Setup");
		formToolkit.adapt(grpRemoteSetup);
		formToolkit.paintBordersFor(grpRemoteSetup);

		Button btnConnect = new Button(grpRemoteSetup, SWT.FLAT);
		btnConnect.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				display.asyncExec(new Runnable() {
					public void run() {
						try {
							networkManager.connect();
						} catch (Exception e) {
						}
					}
				});
			}
		});

		GridData gd_btnConnect = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnConnect.heightHint = 32;
		btnConnect.setLayoutData(gd_btnConnect);
		formToolkit.adapt(btnConnect, true, true);
		btnConnect.setText("Connect to Robot");

		Button btnInitialize = new Button(grpRemoteSetup, SWT.FLAT | SWT.CENTER);
		btnInitialize.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.sendCommand(new Command(1, ""));
			}
		});
		GridData gd_btnInitialize = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnInitialize.heightHint = 32;
		btnInitialize.setLayoutData(gd_btnInitialize);
		btnInitialize.setText("Robot Initialization");
		formToolkit.adapt(btnInitialize, true, true);

		Group grpCameraView = new Group(composite, SWT.NONE);
		grpCameraView.setLayout(new FillLayout(SWT.HORIZONTAL));
		GridData gd_grpCameraView = new GridData(SWT.FILL, SWT.FILL, false, false, 1, 2);
		gd_grpCameraView.heightHint = 256;
		gd_grpCameraView.widthHint = 356;
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

		btnUp = new Button(grpRobotMovement, SWT.FLAT | SWT.CENTER);
		btnUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				// networkManager.sendCommand(new Command(3, "F"));
				networkManager.sendCommand(new Command(2, "A"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-up-01_186407.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnLeft = new Button(grpRobotMovement, SWT.FLAT);
		btnLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "L"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-left-01_186410.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnRight = new Button(grpRobotMovement, SWT.FLAT);
		btnRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "R"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-right-01_186409.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnDown = new Button(grpRobotMovement, SWT.FLAT | SWT.CENTER);
		btnDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "B"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnDown.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-down-01_186411.png"));
		new Label(grpRobotMovement, SWT.NONE);

		Group grpMapView = new Group(composite, SWT.NONE);
		grpMapView.setLayout(new FillLayout(SWT.HORIZONTAL));
		grpMapView.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 4));
		grpMapView.setText("Map View");
		formToolkit.adapt(grpMapView);
		formToolkit.paintBordersFor(grpMapView);

		Composite compositeMap = new Composite(grpMapView, SWT.NONE);
		formToolkit.adapt(compositeMap);
		formToolkit.paintBordersFor(compositeMap);
		compositeMap.setLayout(new GridLayout(1, false));

		canvas = new Canvas(compositeMap, SWT.NONE);
		canvas.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.adapt(canvas);
		formToolkit.paintBordersFor(canvas);
		canvas.setLayout(new GridLayout(1, false));

		canvas.addPaintListener(new PaintListener() {
			public void paintControl(PaintEvent e) {
				mazeDrawer.draw(e);
			}
		});

		Group grpMode = new Group(composite, SWT.NONE);
		grpMode.setLayout(new GridLayout(1, false));
		grpMode.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		grpMode.setText("Mode Selection");
		formToolkit.adapt(grpMode);
		formToolkit.paintBordersFor(grpMode);

		Listener modeListener = new Listener() {
			public void handleEvent(Event e) {
				Control[] children = grpMode.getChildren();
				for (int i = 0; i < children.length; i++) {
					Control child = children[i];
					if (e.widget != child && child instanceof Button && (child.getStyle() & SWT.TOGGLE) != 0) {
						((Button) child).setSelection(false);
					}
				}
				((Button) e.widget).setSelection(true);
			}
		};

		btnAuto = new Button(grpMode, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnAuto.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.sendCommand(new Command(2, "A"));
			}
		});
		GridData gd_btnAuto = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnAuto.heightHint = 32;
		btnAuto.setLayoutData(gd_btnAuto);
		btnAuto.setText("Autonomous");
		btnAuto.addListener(SWT.Selection, modeListener);

		btnManual = new Button(grpMode, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnManual.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.sendCommand(new Command(2, "M"));
			}
		});
		GridData gd_btnManual = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_btnManual.heightHint = 32;
		btnManual.setLayoutData(gd_btnManual);
		btnManual.setText("Manual");
		btnManual.addListener(SWT.Selection, modeListener);

		Label label = new Label(grpMode, SWT.SEPARATOR | SWT.HORIZONTAL);
		GridData gd_label = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_label.heightHint = 10;
		label.setLayoutData(gd_label);
		formToolkit.adapt(label, true, true);

		lblSuspended = new CLabel(grpMode, SWT.BORDER);
		GridData gd_lblSuspended = new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1);
		gd_lblSuspended.heightHint = 32;
		lblSuspended.setLayoutData(gd_lblSuspended);
		lblSuspended.setForeground(SWTResourceManager.getColor(SWT.COLOR_GRAY));
		lblSuspended.setAlignment(SWT.CENTER);
		formToolkit.adapt(lblSuspended);
		formToolkit.paintBordersFor(lblSuspended);
		lblSuspended.setText("Suspended");

		Group grpPanTilt = new Group(composite, SWT.NONE);
		grpPanTilt.setLayout(new GridLayout(3, false));
		grpPanTilt.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		grpPanTilt.setText("Camera Pan/Tilt");
		formToolkit.adapt(grpPanTilt);
		formToolkit.paintBordersFor(grpPanTilt);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraUp = new Button(grpPanTilt, SWT.FLAT);
		btnCameraUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "U"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_up_alt1_118743.png"));
		formToolkit.adapt(btnCameraUp, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraLeft = new Button(grpPanTilt, SWT.FLAT);
		btnCameraLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "L"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_left_alt1_118748.png"));
		formToolkit.adapt(btnCameraLeft, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraRight = new Button(grpPanTilt, SWT.FLAT);
		btnCameraRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "R"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_right_alt1_118746.png"));
		formToolkit.adapt(btnCameraRight, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraDown = new Button(grpPanTilt, SWT.FLAT);
		btnCameraDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "D"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "S"));
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
		compositeStatus.setFont(SWTResourceManager.getFont(".SF NS Text", 11, SWT.BOLD));
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

		lblConnected = new Label(compositeStatus, SWT.NONE);
		GridData gd_lblConnected = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_lblConnected.widthHint = 30;
		lblConnected.setLayoutData(gd_lblConnected);
		formToolkit.adapt(lblConnected, true, true);

		Label split0 = new Label(compositeStatus, SWT.SEPARATOR | SWT.VERTICAL);
		GridData gd_split0 = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_split0.heightHint = 10;
		split0.setLayoutData(gd_split0);
		formToolkit.adapt(split0, true, true);

		Label lblTimeElapsed = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblTimeElapsed, true, true);
		lblTimeElapsed.setText("Time Elapsed :");

		lblTime = new Label(compositeStatus, SWT.NONE);
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

		lblRobotMessage = new Label(compositeStatus, SWT.NONE);
		lblRobotMessage.setForeground(SWTResourceManager.getColor(SWT.COLOR_RED));
		lblRobotMessage.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(lblRobotMessage, true, true);

		Group grpDistanceLeft = new Group(grpMonitoringInfo, SWT.NONE);
		GridData gd_grpDistanceLeft = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceLeft.widthHint = 170;
		grpDistanceLeft.setLayoutData(gd_grpDistanceLeft);
		grpDistanceLeft.setLayout(new GridLayout(1, false));
		grpDistanceLeft.setText("Left Distance");
		formToolkit.adapt(grpDistanceLeft);
		formToolkit.paintBordersFor(grpDistanceLeft);

		lblLeftDistance = new Label(grpDistanceLeft, SWT.NONE);
		lblLeftDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblLeftDistance.setFont(SWTResourceManager.getFont(".SF NS Text", 26, SWT.BOLD));
		formToolkit.adapt(lblLeftDistance, true, true);
		lblLeftDistance.setText("0 mm");
		new Label(grpMonitoringInfo, SWT.NONE);

		Group grpDistanceFront = new Group(grpMonitoringInfo, SWT.NONE);
		grpDistanceFront.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		grpDistanceFront.setLayout(new GridLayout(1, false));
		grpDistanceFront.setText("Front Distance");
		formToolkit.adapt(grpDistanceFront);
		formToolkit.paintBordersFor(grpDistanceFront);

		lblFrontDistance = new Label(grpDistanceFront, SWT.NONE);
		lblFrontDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblFrontDistance.setText("0 mm");
		lblFrontDistance.setFont(SWTResourceManager.getFont(".SF NS Text", 26, SWT.BOLD));
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

		lblRightDistance = new Label(grpDistanceRight, SWT.NONE);
		lblRightDistance.setBackground(SWTResourceManager.getColor(SWT.COLOR_TRANSPARENT));
		lblRightDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblRightDistance.setFont(SWTResourceManager.getFont(".SF NS Text", 26, SWT.BOLD));
		formToolkit.adapt(lblRightDistance, true, true);
		lblRightDistance.setText("0 mm");

		TabFolder tabFolder = new TabFolder(composite, SWT.NONE);
		tabFolder.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 3, 1));
		formToolkit.adapt(tabFolder);
		formToolkit.paintBordersFor(tabFolder);

		TabItem tbtmMessageConsole = new TabItem(tabFolder, SWT.NONE);
		tbtmMessageConsole.setText("Message Console");

		txtLogMessge = new Text(tabFolder, SWT.BORDER | SWT.WRAP | SWT.V_SCROLL | SWT.MULTI);
		tbtmMessageConsole.setControl(txtLogMessge);
		txtLogMessge.setFont(SWTResourceManager.getFont(".SF NS Text", 11, SWT.NORMAL));
		formToolkit.adapt(txtLogMessge, true, true);

		TabItem tbtmSettings = new TabItem(tabFolder, SWT.NONE);
		tbtmSettings.setText("Settings");

		Composite compositeSettings = new Composite(tabFolder, SWT.NONE);
		tbtmSettings.setControl(compositeSettings);
		formToolkit.paintBordersFor(compositeSettings);
		compositeSettings.setLayout(new GridLayout(3, false));

		Label lblRobotIp = new Label(compositeSettings, SWT.NONE);
		lblRobotIp.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblRobotIp, true, true);
		lblRobotIp.setText("Robot IP");

		txtIP = new Text(compositeSettings, SWT.BORDER);
		txtIP.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtIP, true, true);

		Button btnSave = new Button(compositeSettings, SWT.NONE);
		btnSave.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				display.syncExec(new Runnable() {
					public void run() {
						ConfigManager configManager = ConfigManager.getInstance();

						try {
							configManager.setRobotIp(txtIP.getText());
							configManager.setRobotPort(Integer.parseInt(txtPort.getText()));
							configManager.setCameraListenport(Integer.parseInt(txtListenPort.getText()));
							configManager.setCameraDatagramMaxSize(Integer.parseInt(txtMaxPacketSize.getText()));
							configManager.setMazeRowCount(Integer.parseInt(txtRowCnt.getText()));
							configManager.setMazeColumnCount(Integer.parseInt(txtColumnCnt.getText()));

							configManager.persist();
							
							Utils.showMessageDialog(shlBlackbeardPirates, "Configuration Saving completed.\n\nFile Path = " + configManager.getConfigFilePath(), SWT.ICON_INFORMATION);
						} catch (Exception ex) {
							RUIMain.this.appendLogMessage(Utils.getStackTrace(ex));
							Utils.showMessageDialog(shlBlackbeardPirates, "Error occurred while saving.\nPlease check the error message in Message Console Tab", SWT.ICON_ERROR);
						}
					}
				});
			}
		});
		btnSave.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 5));
		formToolkit.adapt(btnSave, true, true);
		btnSave.setText("Save");

		Label lblRobotPort = new Label(compositeSettings, SWT.NONE);
		lblRobotPort.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblRobotPort, true, true);
		lblRobotPort.setText("Robot Port");

		txtPort = new Text(compositeSettings, SWT.BORDER);
		txtPort.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtPort, true, true);

		Label lblCameraListenPort = new Label(compositeSettings, SWT.NONE);
		lblCameraListenPort.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblCameraListenPort, true, true);
		lblCameraListenPort.setText("Camera Listen Port");

		txtListenPort = new Text(compositeSettings, SWT.BORDER);
		txtListenPort.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtListenPort, true, true);

		Label lblImageMaxPacket = new Label(compositeSettings, SWT.NONE);
		lblImageMaxPacket.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblImageMaxPacket, true, true);
		lblImageMaxPacket.setText("Image Max Packet Size");

		txtMaxPacketSize = new Text(compositeSettings, SWT.BORDER);
		txtMaxPacketSize.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtMaxPacketSize, true, true);

		Label lblDefaultMaze = new Label(compositeSettings, SWT.NONE);
		lblDefaultMaze.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblDefaultMaze, true, true);
		lblDefaultMaze.setText("Maze Size");

		Composite compositeMaze = new Composite(compositeSettings, SWT.NONE);
		compositeMaze.setLayout(new GridLayout(4, false));
		GridData gd_compositeMaze = new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1);
		gd_compositeMaze.heightHint = 27;
		compositeMaze.setLayoutData(gd_compositeMaze);
		formToolkit.adapt(compositeMaze);
		formToolkit.paintBordersFor(compositeMaze);

		Label lblOfRow = new Label(compositeMaze, SWT.NONE);
		lblOfRow.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblOfRow, true, true);
		lblOfRow.setText("# of Row:");

		txtRowCnt = new Text(compositeMaze, SWT.BORDER);
		txtRowCnt.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtRowCnt, true, true);

		Label lblOfColumn = new Label(compositeMaze, SWT.NONE);
		lblOfColumn.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblOfColumn, true, true);
		lblOfColumn.setText("# of Column");

		txtColumnCnt = new Text(compositeMaze, SWT.BORDER);
		txtColumnCnt.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtColumnCnt, true, true);
		
		TabItem tbtmSimulation = new TabItem(tabFolder, SWT.NONE);
		tbtmSimulation.setText("Simulation");
		
		Composite compositeSimulation = new Composite(tabFolder, SWT.NONE);
		tbtmSimulation.setControl(compositeSimulation);
		formToolkit.paintBordersFor(compositeSimulation);
		compositeSimulation.setLayout(new GridLayout(2, false));
		
		txtCommandMessages = new Text(compositeSimulation, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL | SWT.CANCEL | SWT.MULTI);
		txtCommandMessages.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 2));
		formToolkit.adapt(txtCommandMessages, true, true);
		
		Button btnLoopback = new Button(compositeSimulation, SWT.NONE);
		btnLoopback.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				
			}
		});
		btnLoopback.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1));
		formToolkit.adapt(btnLoopback, true, true);
		btnLoopback.setText("Loopback");
		
		Button btnSend = new Button(compositeSimulation, SWT.NONE);
		btnSend.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1));
		formToolkit.adapt(btnSend, true, true);
		btnSend.setText("Send");
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
	}

	public Label getCameraImageLabel() {
		return this.cameraImage;
	}

	public void appendLogMessage(String message) {
		display.asyncExec(new Runnable() {
			public void run() {
				txtLogMessge.append(String.format("[%s] %s \n", Utils.getLogTime(), message));
			}
		});
	}

	protected void executeCommand(Command command) {
		appendLogMessage(command.toString());

		int cmdType = command.getType();

		switch (cmdType) {
		case 1:
			initialize();
			break;
		case 2:
			changeMode(command.getPayload());
			break;
		case 5:
			changeSensorData(command.getPayload());
			break;
		case 6:
			mazeDrawer.updateMaze(command.getPayload());
			break;
		case 9:
			handleErrorState(command.getPayload());
			break;
		default:
			break;
		}
	}

	private void handleErrorState(String payload) {
		if ("S".equals(payload)) {
			lblRobotMessage.setText("Can not recognize a sign");
		} else if ("P".equals(payload)) {
			lblRobotMessage.setText("Can not find a path to go");
		} else {
			lblRobotMessage.setText("Unknown message");
		}
	}

	public Canvas getMazeCanvas() {
		return canvas;
	}

	private void initialize() {
		mazeDrawer.clear();
		btnManual.notifyListeners(SWT.Selection, new Event());
	}

	// A: autonomous, M : Manual, S : Suspend
	private void changeMode(String mode) {
		if ("A".equals(mode)) {
			btnAuto.setSelection(true);
			setEnableRobotMovement(false);
		} else if ("M".equals(mode) || "S".equals(mode)) {
			btnManual.setSelection(true);
			setEnableRobotMovement(true);
		}

		lblSuspended.setForeground(SWTResourceManager.getColor("S".equals(mode) ? SWT.COLOR_RED : SWT.COLOR_GRAY));
	}

	// Front distance / Left distance / Right distance
	private void changeSensorData(String payload) {
		String[] data = payload.split("/");
		if (data.length != 3)
			return;

		lblFrontDistance.setText(data[0] + " mm");
		lblLeftDistance.setText(data[1] + " mm");
		lblRightDistance.setText(data[2] + " mm");
	}

	public void notify(Command command) {
		display.asyncExec(new Runnable() {
			public void run() {
				executeCommand(command);
			}
		});
	}

	private void setEnableRobotMovement(boolean enabled) {
		btnUp.setEnabled(enabled);
		btnRight.setEnabled(enabled);
		btnDown.setEnabled(enabled);
		btnLeft.setEnabled(enabled);

		btnCameraUp.setEnabled(enabled);
		btnCameraRight.setEnabled(enabled);
		btnCameraDown.setEnabled(enabled);
		btnCameraLeft.setEnabled(enabled);
	}

	public void setNetworkStatus(boolean connected) {
		display.asyncExec(new Runnable() {
			public void run() {
				lblConnected.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/" + (connected ? "connected-16.png" : "disconnected-16.png")));
			}
		});
	}
}
