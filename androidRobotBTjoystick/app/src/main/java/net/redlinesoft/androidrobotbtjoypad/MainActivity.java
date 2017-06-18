package net.redlinesoft.androidrobotbtjoypad;

import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Vibrator;
import android.preference.PreferenceManager;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Map;

import app.akexorcist.bluetotohspp.library.BluetoothSPP;
import app.akexorcist.bluetotohspp.library.BluetoothState;
import app.akexorcist.bluetotohspp.library.DeviceList;

public class MainActivity extends AppCompatActivity {

    private View mDecorView;

    WebView webView;
    ImageView ivUp, ivDown, ivLeft, ivRight, ivA, ivB, ivC, ivD;
    TextView txtResult;
    SharedPreferences prefs;
    BluetoothSPP bt;
    Context context;
    Boolean btConnect = false;
    int RESULT_SETTING = 0;
    int QR_CODE = 1;
    Menu menu;
    CoordinatorLayout coordinatorLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        loadPreference();

        // set color background
        getWindow().getDecorView().setBackgroundColor(getResources().getColor(R.color.colorBackground1));

        // set view
        mDecorView = getWindow().getDecorView();

        // hide system ui
        hideSystemUI();

        // set textview for result
        txtResult = (TextView) findViewById(R.id.txtResult);


        // web View Setting
        webView = (WebView) findViewById(R.id.webView);
        webView.setWebViewClient(new MyBrowser());

        webView.getSettings().setLoadsImagesAutomatically(true);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.getSettings().setDomStorageEnabled(true);
        webView.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
        webView.setScrollBarStyle(View.SCROLLBARS_INSIDE_OVERLAY);
        // webView.loadUrl("http://" + "192.168.1.4:8080");

        // adding listener to the button to load website
        Button runButton = (Button) findViewById(R.id.run_button);
        runButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String ip = prefs.getString("pref_server_ip_key", "192.168.1.4");
                String port = prefs.getString("pref_server_port_key", "8080");

                Log.d("webViewChange", ip + ":" + port);

                webView.loadUrl("http://" + ip + ":" + port);
            }
        });

        // set coordinate layout
        coordinatorLayout = (CoordinatorLayout) findViewById(R.id.coordinateLayout);

        // setup bluetooth
        bt = new BluetoothSPP(context);

        // check connection
        //checkBluetoothState();

        bt.setOnDataReceivedListener(new BluetoothSPP.OnDataReceivedListener() {
            public void onDataReceived(byte[] data, String message) {
                Log.e("MY TAG: ", message);
            }
        });


        // bluetooth listener
        bt.setBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() {
            // the device is connected
            public void onDeviceConnected(String name, String address) {
                // Do something when successfully connected
                //Toast.makeText(getApplicationContext(), "Connected", Toast.LENGTH_SHORT).show();
                Snackbar.make(coordinatorLayout, "Connected", Snackbar.LENGTH_SHORT).show();
                btConnect = true;
                setMenuTitle("Disconnect");
            }

            public void onDeviceDisconnected() {
                // Do something when connection was disconnected
                //Toast.makeText(getApplicationContext(), "Disconnected", Toast.LENGTH_SHORT).show();
                Snackbar.make(coordinatorLayout, "Disconnected", Snackbar.LENGTH_SHORT).show();
                btConnect = false;
                btConnect = true;
                setMenuTitle("Connect");
            }

            public void onDeviceConnectionFailed() {
                // Do something when connection failed
                //Toast.makeText(getApplicationContext(), "Connection Failed", Toast.LENGTH_SHORT).show();
                Snackbar.make(coordinatorLayout, "Connection Failed", Snackbar.LENGTH_SHORT).show();
                btConnect = false;
                setMenuTitle("Connect");
            }
        });


    }


    // calss for the web view
    private class MyBrowser extends WebViewClient {

        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            view.loadUrl(url);
            return true;
        }
    }

    // if the back button was pressed
    @Override
    public void onBackPressed() {

        if (webView.canGoBack()){
            webView.goBack();
            return;
        }
        super.onBackPressed();
    }


    private void checkBluetoothState() {

        if (this.btConnect) {
            bt.disconnect();
        }

        if (bt.isBluetoothEnabled()) {
            bt.setupService();
            bt.startService(BluetoothState.DEVICE_OTHER);
            Snackbar.make(coordinatorLayout, "Choose device to connect", Snackbar.LENGTH_LONG)
                    .setAction("Setup", new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            // load device list
                            Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                            startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                        }
                    }).show();
        } else {
            checkBluetoothEnable();
        }

    }

    public void setTextResult(String button) {
        if (prefs.getBoolean("pref_debug_switch", false)) {
            txtResult.setText(button);
        } else {
            txtResult.setText("");
        }

        if (prefs.getBoolean("pref_vibrate_switch", false)) {
            Vibrator v = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
            v.vibrate(50);
        }
    }

    public void setMenuTitle(String title) {
        // change setting menu
        MenuItem settingsItem = menu.findItem(R.id.mnuBluetooth);
        settingsItem.setTitle(title);
    }

    // send bluetooth data
    public void sendBluetoothData(final String data) {

        final int delay = Integer.parseInt(prefs.getString("pref_delay_list", "0"));

        final Handler handler = new Handler();

        final Runnable r = new Runnable() {
            public void run() {

                bt.send(data, true);
                Log.e("MY TAG : ", data);
            }
        };
        handler.postDelayed(r, delay);
    }


    // load preference (setting)
    public void loadPreference() {
        prefs = PreferenceManager.getDefaultSharedPreferences(this);
        Map<String, ?> keys = prefs.getAll();
        Log.d("LOG", "Keys = " + keys.size() + "");
        if (keys.size() >= 11) {
            for (Map.Entry<String, ?> entry : keys.entrySet()) {
                Log.d("LOG", entry.getKey() + ": " +
                        entry.getValue().toString());
            }
        } else {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Setup button first!");
            builder.setCancelable(false);
            builder.setPositiveButton("Setting", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // button setting
                    Intent i = new Intent(getApplicationContext(), SettingsActivity.class);
                    startActivityForResult(i, RESULT_SETTING);
                }
            });
            builder.setNegativeButton("QRCode", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // scan qrcode
                    qrcodeScanner();
                }
            });
            builder.show();
        }
    }

    // back from activity with a result
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        //super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == BluetoothState.REQUEST_CONNECT_DEVICE) {
            if (resultCode == Activity.RESULT_OK)
                bt.connect(data);

            // setup josypad view
            setupJoyPadView();

        } else if (requestCode == BluetoothState.REQUEST_ENABLE_BT) {
            if (resultCode == Activity.RESULT_OK) {
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
                // setup josypad view
                setupJoyPadView();
            } else {
                // Do something if user doesn't choose any device (Pressed back)
            }
        } else if (requestCode == QR_CODE) {
            if (resultCode == RESULT_OK) {
                String contents = data.getStringExtra("SCAN_RESULT");
                Log.d("LOG", contents);
                try {
                    JSONObject reader = new JSONObject(contents);
                    // set sharepreference
                    // sample json string
                    // {"up": "w 1 1","dw": "w 2 1","lf": "w 4 1","rt": "w 3 1","a": "w 0 1","b": "w 0 0","c": "w 5 3","d": "w 6 3"}
                    prefs = PreferenceManager.getDefaultSharedPreferences(this);
                    SharedPreferences.Editor editor = prefs.edit();
                    editor.putBoolean("pref_debug_switch", false);
                    editor.putBoolean("pref_vibrate_switch", true);
                    editor.putString("pref_delay_list", "0");
                    editor.putString("pref_pos_up", reader.getString("up"));
                    editor.putString("pref_pos_down", reader.getString("dw"));
                    editor.putString("pref_pos_left", reader.getString("lf"));
                    editor.putString("pref_pos_right", reader.getString("rt"));
                    editor.putString("pref_pos_a", reader.getString("a"));
                    editor.putString("pref_pos_b", reader.getString("b"));
                    editor.putString("pref_pos_c", reader.getString("c"));
                    editor.putString("pref_pos_d", reader.getString("d"));
                    editor.commit();
                    Snackbar.make(coordinatorLayout, "Config button complete, let's Play!", Snackbar.LENGTH_LONG).show();
                } catch (JSONException e) {
                    e.printStackTrace();
                    Snackbar.make(coordinatorLayout, "Wrong QRCode!!", Snackbar.LENGTH_LONG).show();
                }

            }
        }
    }


    // setting the pad images and assigning listener to them to send data
    private void setupJoyPadView() {

        ivUp = (ImageView) findViewById(R.id.ivUp);
        ivUp.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_up", "x");
                    Log.d("LOG", "Up=" + button);
                    setTextResult("Up=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivDown = (ImageView) findViewById(R.id.ivDown);
        ivDown.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_down", "x");
                    Log.d("LOG", "Down=" + button);
                    setTextResult("Down=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivLeft = (ImageView) findViewById(R.id.ivLeft);
        ivLeft.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_left", "x");
                    Log.d("LOG", "Left=" + button);
                    setTextResult("Left=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivRight = (ImageView) findViewById(R.id.ivRight);
        ivRight.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_right", "x");
                    Log.d("LOG", "Right=" + button);
                    setTextResult("Right=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivA = (ImageView) findViewById(R.id.ivA);
        ivA.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_a", "x");
                    Log.d("LOG", "A=" + button);
                    setTextResult("A=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivB = (ImageView) findViewById(R.id.ivB);
        ivB.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_b", "x");
                    Log.d("LOG", "B=" + button);
                    setTextResult("B=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });

        ivC = (ImageView) findViewById(R.id.ivC);
        ivC.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_c", "x");
                    Log.d("LOG", "C=" + button);
                    setTextResult("C=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });


        ivD = (ImageView) findViewById(R.id.ivD);
        ivD.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                ImageView iv = (ImageView) v;
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    iv.setImageResource(R.drawable.bg_stick_pressed);
                    String button = prefs.getString("pref_pos_d", "x");
                    Log.d("LOG", "D=" + button);
                    setTextResult("D=" + button);
                    sendBluetoothData(button);
                    return true;
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    iv.setImageResource(R.drawable.bg_stick_unpressed);
                    return true;
                }
                return false;
            }
        });


    }

    // activity destroyed
    @Override
    protected void onDestroy() {
        super.onDestroy();
        bt.stopService();
    }

    // activity resumed
    @Override
    protected void onResume() {
        super.onResume();
    }


    // activity restarted
    @Override
    protected void onRestart() {
        super.onRestart();
        loadPreference();
    }

    // activity started
    @Override
    protected void onStart() {
        super.onStart();
        checkBluetoothEnable();
    }

    //
    private void checkBluetoothEnable() {
        if (!bt.isBluetoothEnabled()) {
            // Do something if bluetooth is disable
            Snackbar.make(coordinatorLayout, "Bluetooth is disable", Snackbar.LENGTH_LONG)
                    .setAction("Turn On", new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                            startActivityForResult(enableBtIntent, BluetoothState.REQUEST_ENABLE_BT);
                        }
                    }).show();
        }
    }

    // making the menu
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        this.menu = menu;
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();

        if (itemId == R.id.mnuSettings) {
            Intent i = new Intent(getApplicationContext(), SettingsActivity.class);
            startActivityForResult(i, RESULT_SETTING);
        } else if (itemId == R.id.mnuBluetooth) {
            checkBluetoothState();
        } else if (itemId == R.id.mnuFullscreen) {
            hideSystemUI();
        } else if (itemId == R.id.mnuScan) {
            qrcodeScanner();
        }

        return super.onOptionsItemSelected(item);
    }


    // starting qrCode activity for scan
    private void qrcodeScanner() {

        //        try {
        //            Intent intent = new Intent("com.google.zxing.client.android.SCAN");
        //            intent.putExtra("SCAN_MODE", "QR_CODE_MODE"); // "PRODUCT_MODE for bar codes
        //            startActivityForResult(intent, QR_CODE);
        //        } catch (Exception e) {
        //            Uri marketUri = Uri.parse("market://details?id=com.google.zxing.client.android");
        //            Intent marketIntent = new Intent(Intent.ACTION_VIEW, marketUri);
        //            startActivity(marketIntent);
        //        }

        Intent i = new Intent(MainActivity.this, ScannerActivity.class);
        startActivityForResult(i, QR_CODE);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        if (hasFocus)
            hideSystemUI();
    }

    // This snippet hides the system bars.
    private void hideSystemUI() {
        // Set the IMMERSIVE flag.
        // Set the content to appear under the system bars so that the content
        // doesn't resize when the system bars hide and show.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            mDecorView.setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                            | View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                            | View.SYSTEM_UI_FLAG_IMMERSIVE
            );
        }
    }

    // This snippet shows the system bars. It does this by removing all the flags
    // except for the ones that make the content appear under the system bars.
    private void showSystemUI() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            mDecorView.setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
        }
    }
}
