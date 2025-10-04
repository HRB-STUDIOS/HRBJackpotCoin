package org.hrbjackpotcoincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class HRB Jackpot CoinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File hrbjackpotcoinDir = new File(getFilesDir().getAbsolutePath() + "/.hrbjackpotcoin");
        if (!hrbjackpotcoinDir.exists()) {
            hrbjackpotcoinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
