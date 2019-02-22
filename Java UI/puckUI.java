package puckUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class puckUI extends JFrame {
	// private variables
	private JToolBar toolbar;
	private JButton btnFile, btnNewPlayer, btnLog, btnConfirm, btnStart, btnStop;
	private JLabel lblStatus, lblName, lblAccel, lblVelo, lblRotation, lblContact;
	private JLabel lblValAccel, lblValVel,lblValRotation, lblValContact;
	private String strNewPly;
	
		// constructor to setup GUI components
		public puckUI() {
			// Retrieve top-level content-pane from JFrame
			Container cp = getContentPane();
			cp.setBackground(Color.DARK_GRAY);
			// cp.setLayout(new GridBagLayout());
			
			// adds tool bar to top of screen
			toolbar = new JToolBar();
			toolbar.setRollover(true);
			toolbar.setFloatable(false);	
			btnFile = new JButton("File");
			toolbar.add(btnFile);
			JPopupMenu dropFile = new JPopupMenu("FileMenu");
			dropFile.add("Connect to puck");
			dropFile.add("Manage player profiles");
			dropFile.add("Create Report");
			btnFile.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					dropFile.show(btnFile, btnFile.getWidth()/2, btnFile.getHeight()/2);
				}
			});
			toolbar.addSeparator();
			
			JButton btnOptions = new JButton("Options");
			toolbar.add(btnOptions);
			JPopupMenu dropOptions = new JPopupMenu("OptionsMenu");
			dropOptions.add("Units");
			dropOptions.add("Profiles");
			btnOptions.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					dropOptions.show(btnOptions, btnOptions.getWidth()/2, btnOptions.getHeight()/2);
				}
			});
			toolbar.addSeparator();
			
			JButton btnHelp = new JButton("Help");
			toolbar.add(btnHelp);
			toolbar.addSeparator();
			
			
			cp.add(toolbar, BorderLayout.NORTH);
			
			// new panel
			JPanel pane = new JPanel(new GridBagLayout());
			pane.setBackground(Color.DARK_GRAY);
			GridBagConstraints c = new GridBagConstraints();
			c.insets = new Insets(8,8,8,8);
			
			// row 1
			lblStatus = new JLabel("<html>Status: Connected<br>Battery: 90%</html>");
			lblStatus.setForeground(Color.GREEN);
			c.gridx = 0;
			c.gridy = 1;
			//c.gridheight = 2;
			//c.fill = GridBagConstraints.VERTICAL;
			pane.add(lblStatus, c);
			
			lblName = new JLabel("John Scott");
			lblName.setForeground(Color.WHITE);
			lblName.setFont(new Font("Arial", Font.BOLD, 46));
			c.gridx = 0;
			c.gridy = 0;
			c.gridwidth = 6;
			c.fill= GridBagConstraints.HORIZONTAL;
			pane.add(lblName, c);
			
			btnNewPlayer = new JButton("New Player");
			c.gridx = 6;
			c.gridy = 1;
			c.gridwidth = 1;
			pane.add(btnNewPlayer, c);
			btnNewPlayer.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					strNewPly = JOptionPane.showInputDialog("Enter player name: ");
					lblName.setText(strNewPly);
				}
			});
			
			// row 2
			btnStart = new JButton("Start");
			c.gridx = 2;
			c.gridy = 7;
			pane.add(btnStart, c);
			
			btnStop = new JButton("Stop");
			c.gridx = 4;
			c.gridy = 7;
			pane.add(btnStop, c);
			
			// Display area
			lblAccel = new JLabel("Acceleration:");
			lblAccel.setForeground(Color.WHITE);
			c.gridx = 1;
			c.gridy = 3;
			c.gridwidth = 3;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblAccel, c);
			
			lblValAccel = new JLabel("62 G");
			lblValAccel.setForeground(Color.WHITE);
			c.gridx = 4;
			c.gridy = 3;
			c.gridwidth = 1;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblValAccel, c);
			
			lblVelo = new JLabel("Velocity: ");
			lblVelo.setForeground(Color.WHITE);
			c.gridx = 1;
			c.gridy = 4;
			c.gridwidth = 3;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblVelo, c);
			
			lblValVel = new JLabel("164 km/h");
			lblValVel.setForeground(Color.WHITE);
			c.gridx = 4;
			c.gridy = 4;
			c.gridwidth = 1;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblValVel, c);
			
			lblRotation = new JLabel("Rotation: ");
			lblRotation.setForeground(Color.WHITE);
			c.gridx = 1;
			c.gridy = 5;
			c.gridwidth = 3;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblRotation, c);
			
			lblValRotation = new JLabel("3800 rpm");
			lblValRotation.setForeground(Color.WHITE);
			c.gridx = 4;
			c.gridy = 5;
			c.gridwidth = 1;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblValRotation, c);
			
			lblContact = new JLabel("Contact: ");
			lblContact.setForeground(Color.WHITE);
			c.gridx = 1;
			c.gridy = 6;
			c.gridwidth = 3;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblContact, c);
			
			lblValContact = new JLabel("33 ms");
			lblValContact.setForeground(Color.WHITE);
			c.gridx = 4;
			c.gridy = 6;
			c.gridwidth = 1;
			c.fill = GridBagConstraints.HORIZONTAL;
			pane.add(lblValContact, c);
			
			// last row
			btnConfirm = new JButton("Save");
			c.gridx = 4;
			c.gridy = 8;
			c.gridwidth = 1;
			pane.add(btnConfirm, c);
			
			btnConfirm.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					// testing csv stuff
					try (PrintWriter writer = new PrintWriter(new File("datastream--.csv"))) {
						
						StringBuilder sb = new StringBuilder();
						
						sb.append("Acceleration, ");
						sb.append("Velocity, ");
						sb.append("Rotation, ");
						sb.append("Contact, ");
						sb.append('\n');
						
						
						sb.append(lblValAccel.getText() + ", ");
						sb.append(lblValVel.getText() + ", ");
						sb.append(lblValRotation.getText() + ", ");
						sb.append(lblValContact.getText() + ", ");
						
						writer.write(sb.toString());
					}
					catch (FileNotFoundException e) {
						System.out.println(e.getMessage());
					}
					
				}
			});
			
			btnLog = new JButton("Log");
			c.gridx = 2;
			c.gridy = 8;
			c.gridwidth = 1;
			pane.add(btnLog, c);
			
			btnLog.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					// calls log frame
					JFrame logFrame = new JFrame("Log");
					String[] columnNames = {"Shot", "Acceleration", "Velocity", "Rotation", "Contact"};
					String[][] shotInfo = { 
							{"1", "62", "164", "3800", "33"}
							
						};
					JTable tblLog = new JTable(shotInfo, columnNames);
					tblLog.setBounds(30, 40, 200, 300);
					
					JScrollPane sp = new JScrollPane(tblLog);
					logFrame.add(sp);
					
					logFrame.setSize(500, 200);
					logFrame.setVisible(true);
				}
			});
			
			// set JFrame
			add(pane);
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			setTitle("Performance Tracking Hockey Puck");
			setSize(750, 500);
			setVisible(true);
		}
	
		// log frame
		public static void logFrame()
		{
			
		}
		
	//main method
	public static void main(String[] args) {
		// calls the constructor in thread
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new puckUI();
			}
		});
	}
	
}
