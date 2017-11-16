package rui;

import java.util.List;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CLabel;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Point;
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
import rui.configure.IConstants;
import rui.maze.MazeDrawer;
import rui.monitor.CameraImageReceiver;
import rui.monitor.NetworkManager;
import rui.utils.Utils;

public class RUIMain {
	protected Shell shell;
	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());
	private Label cameraImage;
	public static Display display;

	private Text txtLogMessge;
	private CameraImageReceiver imageReceiver;
	private NetworkManager networkManager;
	private Canvas canvas;
	private MazeDrawer mazeDrawer;
	private Timer timer;

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
	private Label lblNetworkStatusMessage;

	private Button btnConnect;
	private Button btnInitialize;
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

	private TabFolder tabFolder;
	private Button btnSend;
	private Text txtRuiIP;

	protected boolean isUpPressed;
	protected boolean isRightPressed;
	protected boolean isDownPressed;
	protected boolean isLeftPressed;
	protected boolean isCameraUpPressed;
	protected boolean isCameraRightPressed;
	protected boolean isCameraDownPressed;
	protected boolean isCameraLeftPressed;
	private Text txtRobotParameters;
	protected boolean isAutonomousPressed;
	protected boolean isManualPressed;

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

		shell.open();
		shell.layout();
		shell.setFocus();

		imageReceiver = new CameraImageReceiver(this);
		new Thread(imageReceiver).start();

		timer = new Timer();
		new Thread(timer).start();

		networkManager = new NetworkManager(this);
		mazeDrawer = new MazeDrawer(this);

		setEnableRobotMovement(false);
		setNetworkStatus(false);
		setConfigData();

		display.addFilter(SWT.KeyDown, new Listener() {
			@Override
			public void handleEvent(Event e) {
				if (btnUp.isEnabled() && !(e.widget instanceof Text)) {
					if (e.keyCode == SWT.ARROW_UP) {
						if (isUpPressed)
							return;

						btnUp.setSelection(true);
						btnUp.setFocus();

						networkManager.sendCommand(new Command(3, "F"));
						isUpPressed = true;
					} else if (e.keyCode == SWT.ARROW_RIGHT) {
						if (isRightPressed)
							return;

						btnRight.setSelection(true);
						btnRight.setFocus();

						networkManager.sendCommand(new Command(3, "R"));
						isRightPressed = true;
					} else if (e.keyCode == SWT.ARROW_DOWN) {
						if (isDownPressed)
							return;

						btnDown.setSelection(true);
						btnDown.setFocus();

						networkManager.sendCommand(new Command(3, "B"));
						isDownPressed = true;
					} else if (e.keyCode == SWT.ARROW_LEFT) {
						if (isLeftPressed)
							return;

						btnLeft.setSelection(true);
						btnLeft.setFocus();

						networkManager.sendCommand(new Command(3, "L"));
						isLeftPressed = true;
					}
				}
			}
		});

		display.addFilter(SWT.KeyUp, new Listener() {
			@Override
			public void handleEvent(Event e) {
				if (btnUp.isEnabled() && !(e.widget instanceof Text)) {
					if (e.keyCode == SWT.ARROW_UP) {
						btnUp.setSelection(false);
						networkManager.sendCommand(new Command(3, "S"));
						isUpPressed = false;
					} else if (e.keyCode == SWT.ARROW_RIGHT) {
						btnRight.setSelection(false);
						networkManager.sendCommand(new Command(3, "S"));
						isRightPressed = false;
					} else if (e.keyCode == SWT.ARROW_DOWN) {
						btnDown.setSelection(false);
						networkManager.sendCommand(new Command(3, "S"));
						isDownPressed = false;
					} else if (e.keyCode == SWT.ARROW_LEFT) {
						btnLeft.setSelection(false);
						networkManager.sendCommand(new Command(3, "S"));
						isLeftPressed = false;
					}
				}
			}
		});

		display.addFilter(SWT.KeyDown, new Listener() {
			@Override
			public void handleEvent(Event e) {
				if (btnCameraUp.isEnabled() && !(e.widget instanceof Text)) {
					if (e.character == 'e') {
						if (isCameraUpPressed)
							return;

						btnCameraUp.setSelection(true);
						btnCameraUp.setFocus();

						networkManager.sendCommand(new Command(4, "F"));
						isCameraUpPressed = true;
					} else if (e.character == 'f') {
						if (isCameraRightPressed)
							return;

						btnCameraRight.setSelection(true);
						btnCameraRight.setFocus();

						networkManager.sendCommand(new Command(4, "R"));
						isCameraRightPressed = true;
					} else if (e.character == 'd') {
						if (isCameraDownPressed)
							return;

						btnCameraDown.setSelection(true);
						btnCameraDown.setFocus();

						networkManager.sendCommand(new Command(4, "B"));
						isCameraDownPressed = true;
					} else if (e.character == 's') {
						if (isCameraLeftPressed)
							return;

						btnCameraLeft.setSelection(true);
						btnCameraLeft.setFocus();

						networkManager.sendCommand(new Command(4, "L"));
						isCameraLeftPressed = true;
					}
				}

				if (btnAuto.isEnabled() && !(e.widget instanceof Text) && e.character == 'a') {
					if (isAutonomousPressed)
						return;

					btnAuto.notifyListeners(SWT.Selection, new Event());
					isAutonomousPressed = true;
				}

				if (btnManual.isEnabled() && !(e.widget instanceof Text) && e.character == 'm') {
					if (isManualPressed)
						return;

					btnManual.notifyListeners(SWT.Selection, new Event());
					isManualPressed = true;
				}
			}
		});

		display.addFilter(SWT.KeyUp, new Listener() {
			@Override
			public void handleEvent(Event e) {
				if (btnCameraUp.isEnabled() && !(e.widget instanceof Text)) {
					if (e.character == 'e') {
						btnCameraUp.setSelection(false);
						networkManager.sendCommand(new Command(4, "S"));
						isCameraUpPressed = false;
					} else if (e.character == 'f') {
						btnCameraRight.setSelection(false);
						networkManager.sendCommand(new Command(4, "S"));
						isCameraRightPressed = false;
					} else if (e.character == 'd') {
						btnCameraDown.setSelection(false);
						networkManager.sendCommand(new Command(4, "S"));
						isCameraDownPressed = false;
					} else if (e.character == 's') {
						btnCameraLeft.setSelection(false);
						networkManager.sendCommand(new Command(4, "S"));
						isCameraLeftPressed = false;
					}
				}

				if (btnAuto.isEnabled() && !(e.widget instanceof Text) && e.character == 'a') {
					isAutonomousPressed = false;
				}

				if (btnManual.isEnabled() && !(e.widget instanceof Text) && e.character == 'm') {
					isManualPressed = false;
				}
			}
		});

		shell.addListener(SWT.Close, new Listener() {
			public void handleEvent(Event event) {
				if (imageReceiver != null)
					imageReceiver.close();

				if (networkManager != null)
					networkManager.disconnect();

				SWTResourceManager.dispose();
			}
		});

		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	class Timer implements Runnable {
		private int time = -1;
		private boolean isPaused = false;

		@Override
		public void run() {
			while (!shell.isDisposed()) {
				if (time != -1 && !isPaused) {
					display.syncExec(new Runnable() {
						public void run() {
							lblTime.setText(time++ + IConstants.SECOND);
						}
					});
				}

				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
		}

		public void reset() {
			isPaused = false;
			time = 0;
		}

		public void toggle() {
			isPaused = !isPaused;
		}

		public void pause() {
			isPaused = true;
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
		this.txtRuiIP.setText(configManager.getRuiIp());
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.setMinimumSize(new Point(1400, 800));
		shell.setText("Blackbeard Pirates");
		shell.setLayout(new GridLayout(1, false));
		shell.setMaximized(true);

		Composite composite = new Composite(shell, SWT.NONE);
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

		btnConnect = new Button(grpRemoteSetup, SWT.FLAT);
		btnConnect.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/wi-fi.png"));
		btnConnect.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				display.asyncExec(new Runnable() {
					public void run() {
						try {
							if (networkManager.connect()) {
								networkManager.sendCommand(new Command(1, ConfigManager.getInstance().getRuiIp() + "," + ConfigManager.getInstance().getRobotParameters()));
							}
						} catch (Exception e) {
							e.printStackTrace();
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

		btnInitialize = new Button(grpRemoteSetup, SWT.FLAT | SWT.CENTER);
		btnInitialize.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				networkManager.sendCommand(new Command(1, ConfigManager.getInstance().getRuiIp() + "," + ConfigManager.getInstance().getRobotParameters()));
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
		gd_grpCameraView.widthHint = 330;
		grpCameraView.setLayoutData(gd_grpCameraView);
		grpCameraView.setText("Camera View");
		formToolkit.adapt(grpCameraView);
		formToolkit.paintBordersFor(grpCameraView);

		Composite compositeCamera = new Composite(grpCameraView, SWT.NONE);
		formToolkit.adapt(compositeCamera);
		formToolkit.paintBordersFor(compositeCamera);
		compositeCamera.setLayout(new GridLayout(1, false));

		cameraImage = new Label(compositeCamera, SWT.NONE);
		cameraImage.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.adapt(cameraImage, true, true);

		Group grpRobotMovement = new Group(composite, SWT.NONE);
		grpRobotMovement.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		GridLayout gl_grpRobotMovement = new GridLayout(3, false);
		grpRobotMovement.setLayout(gl_grpRobotMovement);
		grpRobotMovement.setText("Robot Movement");
		formToolkit.adapt(grpRobotMovement);
		formToolkit.paintBordersFor(grpRobotMovement);

		new Label(grpRobotMovement, SWT.NONE);

		btnUp = new Button(grpRobotMovement, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "F"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-up-01_186407.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnLeft = new Button(grpRobotMovement, SWT.FLAT | SWT.TOGGLE);
		btnLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "L"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-left-01_186410.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnRight = new Button(grpRobotMovement, SWT.FLAT | SWT.TOGGLE);
		btnRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "R"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(3, "S"));
			}
		});
		btnRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow-right-01_186409.png"));
		new Label(grpRobotMovement, SWT.NONE);

		btnDown = new Button(grpRobotMovement, SWT.FLAT | SWT.TOGGLE | SWT.CENTER);
		btnDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(3, "B"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
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
				if (mazeDrawer != null)
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

		btnCameraUp = new Button(grpPanTilt, SWT.FLAT | SWT.TOGGLE);
		btnCameraUp.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "U"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraUp.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_up_alt1_118743.png"));
		formToolkit.adapt(btnCameraUp, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraLeft = new Button(grpPanTilt, SWT.FLAT | SWT.TOGGLE);
		btnCameraLeft.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "L"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraLeft.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_left_alt1_118748.png"));
		formToolkit.adapt(btnCameraLeft, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraRight = new Button(grpPanTilt, SWT.FLAT | SWT.TOGGLE);
		btnCameraRight.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "R"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraRight.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_right_alt1_118746.png"));
		formToolkit.adapt(btnCameraRight, true, true);
		new Label(grpPanTilt, SWT.NONE);

		btnCameraDown = new Button(grpPanTilt, SWT.FLAT | SWT.TOGGLE);
		btnCameraDown.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				networkManager.sendCommand(new Command(4, "D"));
			}

			@Override
			public void mouseUp(MouseEvent e) {
				((Button) e.widget).setSelection(false);
				networkManager.sendCommand(new Command(4, "S"));
			}
		});
		btnCameraDown.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/if_arrow_down_alt1_118751.png"));
		formToolkit.adapt(btnCameraDown, true, true);
		new Label(grpPanTilt, SWT.NONE);

		Group grpMonitoringInfo = new Group(composite, SWT.NONE);
		grpMonitoringInfo.setLayout(new GridLayout(1, false));
		grpMonitoringInfo.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 3, 1));
		grpMonitoringInfo.setText("Monitoring Information");
		formToolkit.adapt(grpMonitoringInfo);
		formToolkit.paintBordersFor(grpMonitoringInfo);

		Composite compositeStatus = new Composite(grpMonitoringInfo, SWT.NONE);
		compositeStatus.setFont(SWTResourceManager.getFont(".SF NS Text", 11, SWT.BOLD));
		compositeStatus.setBackground(SWTResourceManager.getColor(SWT.COLOR_TRANSPARENT));
		compositeStatus.setLayout(new GridLayout(6, false));
		GridData gd_compositeStatus = new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1);
		gd_compositeStatus.heightHint = 25;
		compositeStatus.setLayoutData(gd_compositeStatus);
		formToolkit.adapt(compositeStatus);
		formToolkit.paintBordersFor(compositeStatus);

		Label lblNetworkStatus = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblNetworkStatus, true, true);
		lblNetworkStatus.setText("Network Status :");

		lblConnected = new Label(compositeStatus, SWT.NONE);
		GridData gd_lblConnected = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_lblConnected.widthHint = 20;
		lblConnected.setLayoutData(gd_lblConnected);
		formToolkit.adapt(lblConnected, true, true);

		lblNetworkStatusMessage = new Label(compositeStatus, SWT.NONE);
		lblNetworkStatusMessage.setForeground(SWTResourceManager.getColor(SWT.COLOR_RED));
		GridData gd_lblNetworkState = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_lblNetworkState.widthHint = 150;
		lblNetworkStatusMessage.setLayoutData(gd_lblNetworkState);

		Label split0 = new Label(compositeStatus, SWT.SEPARATOR | SWT.VERTICAL);
		GridData gd_split0 = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_split0.heightHint = 10;
		split0.setLayoutData(gd_split0);
		formToolkit.adapt(split0, true, true);

		Label lblRobotStatus = new Label(compositeStatus, SWT.NONE);
		formToolkit.adapt(lblRobotStatus, true, true);
		lblRobotStatus.setText("Robot Status :");

		lblRobotMessage = new Label(compositeStatus, SWT.NONE);
		lblRobotMessage.setForeground(SWTResourceManager.getColor(SWT.COLOR_RED));
		lblRobotMessage.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(lblRobotMessage, true, true);

		Composite compositeDistance = new Composite(grpMonitoringInfo, SWT.NONE);
		compositeDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		formToolkit.adapt(compositeDistance);
		formToolkit.paintBordersFor(compositeDistance);
		compositeDistance.setLayout(new GridLayout(5, false));

		Group grpDistanceLeft = new Group(compositeDistance, SWT.NONE);
		GridData gd_grpDistanceLeft = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceLeft.widthHint = 140;
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

		Group grpDistanceFront = new Group(compositeDistance, SWT.NONE);
		GridData gd_grpDistanceFront = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceFront.widthHint = 150;
		grpDistanceFront.setLayoutData(gd_grpDistanceFront);
		grpDistanceFront.setLayout(new GridLayout(1, false));
		grpDistanceFront.setText("Front Distance");
		formToolkit.adapt(grpDistanceFront);
		formToolkit.paintBordersFor(grpDistanceFront);

		lblFrontDistance = new Label(grpDistanceFront, SWT.NONE);
		lblFrontDistance.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblFrontDistance.setText("0" + IConstants.MM);
		lblFrontDistance.setFont(SWTResourceManager.getFont(".SF NS Text", 26, SWT.BOLD));
		lblFrontDistance.setBounds(0, 0, 155, 37);
		formToolkit.adapt(lblFrontDistance, true, true);

		Group grpDistanceRight = new Group(compositeDistance, SWT.NONE);
		GridData gd_grpDistanceRight = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_grpDistanceRight.widthHint = 150;
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
		lblRightDistance.setText("0" + IConstants.MM);

		Label label_1 = new Label(compositeDistance, SWT.SEPARATOR | SWT.VERTICAL);
		formToolkit.adapt(label_1, true, true);

		Group grpTimeElapsed = new Group(compositeDistance, SWT.NONE);
		grpTimeElapsed.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		grpTimeElapsed.setLayout(new GridLayout(1, false));
		grpTimeElapsed.setText("Time Elapsed");
		formToolkit.adapt(grpTimeElapsed);
		formToolkit.paintBordersFor(grpTimeElapsed);

		lblTime = new Label(grpTimeElapsed, SWT.NONE);
		lblTime.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseDown(MouseEvent e) {
				timer.toggle();
			}
		});
		lblTime.setAlignment(SWT.CENTER);
		lblTime.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1));
		lblTime.setFont(SWTResourceManager.getFont(".SF NS Text", 26, SWT.BOLD));
		formToolkit.adapt(lblTime, true, true);
		lblTime.setText("0 s");

		tabFolder = new TabFolder(composite, SWT.NONE);
		tabFolder.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 3, 1));
		formToolkit.adapt(tabFolder);
		formToolkit.paintBordersFor(tabFolder);

		TabItem tbtmMessageConsole = new TabItem(tabFolder, SWT.NONE);
		tbtmMessageConsole.setText("Message Console");

		Composite compositeConsole = new Composite(tabFolder, SWT.NONE);
		tbtmMessageConsole.setControl(compositeConsole);
		formToolkit.paintBordersFor(compositeConsole);
		compositeConsole.setLayout(new GridLayout(2, false));

		txtLogMessge = new Text(compositeConsole, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL | SWT.CANCEL | SWT.MULTI);
		txtLogMessge.setEditable(false);
		GridData gd_txtLogMessge = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
		gd_txtLogMessge.widthHint = 150;
		txtLogMessge.setLayoutData(gd_txtLogMessge);
		txtLogMessge.setFont(SWTResourceManager.getFont(".SF NS Text", 11, SWT.NORMAL));
		formToolkit.adapt(txtLogMessge, true, true);

		Button btnClear = new Button(compositeConsole, SWT.NONE);
		btnClear.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				display.syncExec(new Runnable() {
					public void run() {
						txtLogMessge.setText("");
					}
				});
			}
		});
		btnClear.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1));
		formToolkit.adapt(btnClear, true, true);
		btnClear.setText("Clear");

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
							configManager.setRuiIp(txtRuiIP.getText());
							configManager.setRobotParameters(txtRobotParameters.getText());

							configManager.persist();

							Utils.showMessageDialog(shell, IConstants.SAVE_SUCCESS + configManager.getConfigFilePath(), SWT.ICON_INFORMATION);
						} catch (Exception ex) {
							RUIMain.this.appendLogMessage(Utils.getStackTrace(ex));
							Utils.showMessageDialog(shell, IConstants.SAVE_ERROR, SWT.ICON_ERROR);
						}
					}
				});
			}
		});
		btnSave.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 7));
		formToolkit.adapt(btnSave, true, true);
		btnSave.setText("Save");

		Label lblRobotPort = new Label(compositeSettings, SWT.NONE);
		lblRobotPort.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblRobotPort, true, true);
		lblRobotPort.setText("Robot Port");

		txtPort = new Text(compositeSettings, SWT.BORDER);
		txtPort.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtPort, true, true);

		Label lblRobotParameters = new Label(compositeSettings, SWT.NONE);
		lblRobotParameters.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblRobotParameters, true, true);
		lblRobotParameters.setText("Robot Parameters");

		txtRobotParameters = new Text(compositeSettings, SWT.BORDER);
		txtRobotParameters.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtRobotParameters, true, true);

		Label lblRuiLocalIp = new Label(compositeSettings, SWT.NONE);
		lblRuiLocalIp.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(lblRuiLocalIp, true, true);
		lblRuiLocalIp.setText("RUI IP");

		txtRuiIP = new Text(compositeSettings, SWT.BORDER);
		txtRuiIP.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		formToolkit.adapt(txtRuiIP, true, true);

		Label lblCameraListenPort = new Label(compositeSettings, SWT.NONE);
		GridData gd_lblCameraListenPort = new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1);
		gd_lblCameraListenPort.horizontalIndent = 10;
		lblCameraListenPort.setLayoutData(gd_lblCameraListenPort);
		formToolkit.adapt(lblCameraListenPort, true, true);
		lblCameraListenPort.setText("RUI Camera Listen Port");

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
		txtCommandMessages.setFont(SWTResourceManager.getFont(".SF NS Text", 11, SWT.NORMAL));
		txtCommandMessages.setText(
				"{type=10, payload=} \n{type=7, payload=M}\n\n\n{type=6, payload={0,0,Y,S,Y,N,N,Y,Y,N,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,S,N,N,N,N,N,N,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,S,N,N,N,N,Y,Y,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,E,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,E,N,N,Y,Y,N,Y,N,G,,S,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,S,N,Y,N,N,Y,N,N,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,W,N,N,N,N,Y,Y,N,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,,N,N,N,N,Y,Y,N,,,,}&{2,1,Y,E,N,N,N,Y,N,Y,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,N,N,N,N,N,Y,Y,N,,,,}&{2,1,Y,,N,N,N,Y,N,Y,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,N,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,,N,N,N,N,Y,Y,N,,,,}&{2,1,Y,,N,N,N,Y,N,Y,Y,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,,N,N,N,N,Y,Y,N,,,,}&{2,1,Y,,N,N,N,Y,N,Y,Y,,,,}&{0,2,Y,W,N,N,N,Y,Y,N,N,,,,}}\n{type=6, payload={0,0,Y,,Y,N,N,Y,Y,N,Y,,,,}&{1,0,Y,,N,N,N,N,N,N,Y,,,,}&{2,0,Y,,N,N,N,N,Y,Y,Y,,,,}&{1,1,Y,,N,N,Y,Y,N,Y,N,G,,S,}&{1,2,Y,,N,Y,N,N,Y,N,N,,,,}&{2,2,Y,,N,N,N,N,Y,Y,N,,,,}&{2,1,Y,,N,N,N,Y,N,Y,Y,,,,}&{0,2,Y,,N,N,N,Y,Y,N,N,,,,}&{0,1,Y,E,N,N,N,Y,N,Y,Y,,,,}}\n\n\n\n\n\n\n{type=5, payload=0/0/0}\n{type=5, payload=123/456/789}\n{type=5, payload=232/67/623}\n{type=5, payload=1/3/2}\n\n{type=8, payload=E/Warning Collision}\n\n{type=2, payload=A} \n{type=2, payload=M} \n\n{type=8, payload=E/Cannot recoginize signs}\n{type=7, payload=S}\n{type=7, payload=M}\n\n{type=8, payload=N/Complete}\n\n{type=9, payload=} ");
		GridData gd_txtCommandMessages = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 2);
		gd_txtCommandMessages.widthHint = 150;
		txtCommandMessages.setLayoutData(gd_txtCommandMessages);
		formToolkit.adapt(txtCommandMessages, true, true);

		Button btnLoopback = new Button(compositeSimulation, SWT.NONE);
		btnLoopback.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				simulateCommands(true);
			}
		});
		btnLoopback.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1));
		formToolkit.adapt(btnLoopback, true, true);
		btnLoopback.setText("Loopback");

		btnSend = new Button(compositeSimulation, SWT.NONE);
		btnSend.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				simulateCommands(false);
			}
		});
		btnSend.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1));
		formToolkit.adapt(btnSend, true, true);
		btnSend.setText("Send");
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
		new Label(composite, SWT.NONE);
	}

	private void simulateCommands(boolean isLoopback) {
		String selectedText = txtCommandMessages.getSelectionText();
		String str = Utils.isEmpty(selectedText) ? txtCommandMessages.getText() : selectedText;

		new Thread() {
			public void run() {
				List<Command> commands = Command.getCommandList(str);

				for (Command command : commands) {
					try {
						if (isLoopback)
							RUIMain.this.notify(command);
						else
							networkManager.sendCommand(command);

						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
	}

	public Label getCameraImageLabel() {
		return this.cameraImage;
	}

	public void appendLogMessage(String message) {
		display.asyncExec(new Runnable() {
			public void run() {
				if (!shell.isDisposed())
					txtLogMessge.append(String.format("[%s] %s \n", Utils.getLogTime(), message));
			}
		});
	}

	private void executeCommand(Command command) {
		int cmdType = command.getType();

		if (cmdType != 5) {
			appendLogMessage(command.toString());
		}

		switch (cmdType) {
		case 1:
		case 10:
			initialize();
			break;
		case 5:
			changeSensorData(command.getPayload());
			break;
		case 6:
			mazeDrawer.updateMaze(command.getPayload());
			break;
		case 2:
		case 7:
			changeMode(command.getPayload());
			break;
		case 8:
			changeStatusMessage(command.getPayload());
			break;
		case 9:
			setMissionCompleted();
			break;
		}
	}

	private void setMissionCompleted() {
		timer.pause();
		Utils.showMessageDialog(shell, IConstants.MISSION_COMPLETED, SWT.ICON_INFORMATION);
	}

	private void changeStatusMessage(String payload) {
		String[] tokens = payload.split("/", -1);
		if (tokens.length != 2)
			return;

		Color color = SWTResourceManager.getColor("E".equals(tokens[0]) ? SWT.COLOR_RED : SWT.COLOR_BLACK);

		lblRobotMessage.setForeground(color);
		lblRobotMessage.setText(tokens[1]);
	}

	public Canvas getMazeCanvas() {
		return canvas;
	}

	private void initialize() {
		mazeDrawer.clear();

		changeStatusMessage("N/");
		changeSensorData("0/0/0");

		txtLogMessge.setText("");
		timer.reset();
	}

	private void changeMode(String mode) {
		if ("A".equals(mode)) {
			btnAuto.setSelection(true);
			btnManual.setSelection(false);

			setEnableRobotMovement(false);
		} else if ("M".equals(mode) || "S".equals(mode)) {
			btnAuto.setSelection(false);
			btnManual.setSelection(true);

			setEnableRobotMovement(true);
		}

		Color color = SWTResourceManager.getColor("S".equals(mode) ? SWT.COLOR_RED : SWT.COLOR_GRAY);
		lblSuspended.setForeground(color);
	}

	private void changeSensorData(String payload) {
		String[] data = payload.split("/");
		if (data.length != 3)
			return;

		lblFrontDistance.setText(data[0] + IConstants.MM);
		lblLeftDistance.setText(data[1] + IConstants.MM);
		lblRightDistance.setText(data[2] + IConstants.MM);
	}

	public void notify(Command command) {
		display.asyncExec(new Runnable() {
			public void run() {
				if (!shell.isDisposed())
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
				if (!shell.isDisposed()) {
					lblConnected.setImage(SWTResourceManager.getImage(RUIMain.class, "/resources/" + (connected ? "connected-16.png" : "disconnected-16.png")));
					lblNetworkStatusMessage.setText(connected ? "" : "Network is not connected");
				}
			}
		});
	}

	public Shell getShell() {
		return this.shell;
	}
}
