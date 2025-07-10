package tech.krzys.linuxisobuilder

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import tech.krzys.linuxisobuilder.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setupDistroSpinner()

        binding.buttonGenerate.setOnClickListener {
            generateCommand()
        }
    }

    private fun setupDistroSpinner() {
        val distros = listOf("Select a Distribution...", "Debian", "Ubuntu", "Fedora", "Arch Linux")
        val adapter = ArrayAdapter(this, android.R.layout.simple_spinner_item, distros)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        binding.spinnerDistro.adapter = adapter

        binding.spinnerDistro.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                updateVersionSpinner(distros[position])
            }
            override fun onNothingSelected(parent: AdapterView<*>?) {}
        }
    }

    private fun updateVersionSpinner(distro: String) {
        val versions = when (distro) {
            "Debian" -> listOf("12 (bookworm)", "11 (bullseye)", "unstable (sid)")
            "Ubuntu" -> listOf("24.04 LTS (noble)", "22.04 LTS (jammy)")
            "Fedora" -> listOf("42", "41", "Rawhide")
            "Arch Linux" -> listOf("Rolling Release")
            else -> listOf("Select a distribution first")
        }
        val adapter = ArrayAdapter(this, android.R.layout.simple_spinner_item, versions)
        binding.spinnerVersion.adapter = adapter
    }
    
    private fun generateCommand() {
        // This is a placeholder to demonstrate functionality.
        val distro = binding.spinnerDistro.selectedItem.toString()
        val version = binding.spinnerVersion.selectedItem.toString()
        
        if (distro.contains("Select")) {
            binding.textOutput.text = "Error: Please select a valid distribution."
            return
        }

        val command = "Example: lb config -d ${version.substringAfter("(").substringBefore(")")}"
        binding.textOutput.text = command
    }
}
