package com.androidsrc.client;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client extends AsyncTask<Void, Void, Void> {

	String dstAddress;
	int dstPort;
	String response = "";
	TextView textResponse;

	Client(String addr, int port,TextView textResponse) {
		dstAddress = addr;
		dstPort = port;
		this.textResponse=textResponse;
	}

	@Override
	protected Void doInBackground(Void... arg0) {
		Socket socket = null;

		try {

			socket = new Socket(dstAddress, dstPort);

			 ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(1024);
			 byte[] buffer = new byte[1024];

			int bytesRead;

			//Write to socket
			DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream()) ;
			dataOutputStream.write("G".getBytes());
			Log.v("writing :","write to socket");
			dataOutputStream.flush();




			/*
			* Read form socket as array of values
			* */
			ObjectInputStream objectInputStream = new ObjectInputStream(socket.getInputStream()) ;
			Float[] values = (Float[]) objectInputStream.readObject();
			System.out.println(values.length);
			System.out.println(values[0]);


//			

			/*
			* Read from socket as input stream
			* */
//	      while ((bytesRead = socket.getInputStream().read(buffer)) != -1) {
//			  byteArrayOutputStream.write(buffer, 0, bytesRead);
//			  response += byteArrayOutputStream.toString("UTF-8");
//
//
//			}
		} catch (UnknownHostException e) {

			e.printStackTrace();
			response = "UnknownHostException: " + e.toString();
		} catch (IOException e) {

			e.printStackTrace();
			response = "IOException: " + e.toString();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} finally {
			if (socket != null) {
				try {
					socket.close();
				} catch (IOException e) {

					e.printStackTrace();
				}
			}
		}
		return null;
	}

	@Override
	protected void onPostExecute(Void result) {
		textResponse.setText(response);
		super.onPostExecute(result);
		Log.v("onPostExecute","doing well !");
	}

}
