namespace SonicRModManager
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.components = new System.ComponentModel.Container();
			System.Windows.Forms.Label label5;
			System.Windows.Forms.Label label2;
			System.Windows.Forms.Label label1;
			this.saveButton = new System.Windows.Forms.Button();
			this.saveAndPlayButton = new System.Windows.Forms.Button();
			this.installButton = new System.Windows.Forms.Button();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.configureModButton = new System.Windows.Forms.Button();
			this.modBottomButton = new System.Windows.Forms.Button();
			this.modTopButton = new System.Windows.Forms.Button();
			this.buttonNewMod = new System.Windows.Forms.Button();
			this.buttonRefreshModList = new System.Windows.Forms.Button();
			this.modDescription = new System.Windows.Forms.Label();
			this.modDownButton = new System.Windows.Forms.Button();
			this.modUpButton = new System.Windows.Forms.Button();
			this.modListView = new System.Windows.Forms.ListView();
			this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.tabPage2 = new System.Windows.Forms.TabPage();
			this.codesCheckedListBox = new System.Windows.Forms.CheckedListBox();
			this.tabPage3 = new System.Windows.Forms.TabPage();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.comboResolutionPreset = new System.Windows.Forms.ComboBox();
			this.windowedCheckBox = new System.Windows.Forms.CheckBox();
			this.maintainWindowAspectRatioCheckBox = new System.Windows.Forms.CheckBox();
			this.windowWidth = new System.Windows.Forms.NumericUpDown();
			this.windowHeight = new System.Windows.Forms.NumericUpDown();
			this.customWindowSizeCheckBox = new System.Windows.Forms.CheckBox();
			this.stretchFullscreenCheckBox = new System.Windows.Forms.CheckBox();
			this.forceAspectRatioCheckBox = new System.Windows.Forms.CheckBox();
			this.horizontalResolution = new System.Windows.Forms.NumericUpDown();
			this.windowedFullscreenCheckBox = new System.Windows.Forms.CheckBox();
			this.verticalResolution = new System.Windows.Forms.NumericUpDown();
			this.tabPage4 = new System.Windows.Forms.TabPage();
			this.installURLHandlerButton = new System.Windows.Forms.Button();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.buttonCheckForUpdates = new System.Windows.Forms.Button();
			this.label4 = new System.Windows.Forms.Label();
			this.checkUpdateModsStartup = new System.Windows.Forms.CheckBox();
			this.numericUpdateFrequency = new System.Windows.Forms.NumericUpDown();
			this.comboUpdateFrequency = new System.Windows.Forms.ComboBox();
			this.checkUpdateStartup = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.debugFileCheckBox = new System.Windows.Forms.CheckBox();
			this.debugConsoleCheckBox = new System.Windows.Forms.CheckBox();
			this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.modContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.openFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.checkForUpdatesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.verifyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.forceUpdateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.uninstallToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
			this.developerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.generateManifestToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			label5 = new System.Windows.Forms.Label();
			label2 = new System.Windows.Forms.Label();
			label1 = new System.Windows.Forms.Label();
			this.tabControl1.SuspendLayout();
			this.tabPage1.SuspendLayout();
			this.tabPage2.SuspendLayout();
			this.tabPage3.SuspendLayout();
			this.groupBox3.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.windowWidth)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.windowHeight)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.horizontalResolution)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.verticalResolution)).BeginInit();
			this.tabPage4.SuspendLayout();
			this.groupBox4.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpdateFrequency)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.modContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// label5
			// 
			label5.AutoSize = true;
			label5.Location = new System.Drawing.Point(6, 44);
			label5.Name = "label5";
			label5.Size = new System.Drawing.Size(60, 13);
			label5.TabIndex = 17;
			label5.Text = "Resolution:";
			// 
			// label2
			// 
			label2.AutoSize = true;
			label2.Location = new System.Drawing.Point(219, 91);
			label2.Name = "label2";
			label2.Size = new System.Drawing.Size(12, 13);
			label2.TabIndex = 13;
			label2.Text = "x";
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Location = new System.Drawing.Point(140, 46);
			label1.Name = "label1";
			label1.Size = new System.Drawing.Size(12, 13);
			label1.TabIndex = 7;
			label1.Text = "x";
			// 
			// saveButton
			// 
			this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.saveButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.saveButton.Location = new System.Drawing.Point(87, 370);
			this.saveButton.Name = "saveButton";
			this.saveButton.Size = new System.Drawing.Size(75, 22);
			this.saveButton.TabIndex = 102;
			this.saveButton.Text = "&Save";
			this.saveButton.UseVisualStyleBackColor = true;
			this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
			// 
			// saveAndPlayButton
			// 
			this.saveAndPlayButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.saveAndPlayButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.saveAndPlayButton.Location = new System.Drawing.Point(3, 370);
			this.saveAndPlayButton.Name = "saveAndPlayButton";
			this.saveAndPlayButton.Size = new System.Drawing.Size(78, 22);
			this.saveAndPlayButton.TabIndex = 101;
			this.saveAndPlayButton.Text = "Save && &Play";
			this.saveAndPlayButton.UseVisualStyleBackColor = true;
			this.saveAndPlayButton.Click += new System.EventHandler(this.saveAndPlayButton_Click);
			// 
			// installButton
			// 
			this.installButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.installButton.AutoSize = true;
			this.installButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.installButton.Location = new System.Drawing.Point(168, 370);
			this.installButton.Name = "installButton";
			this.installButton.Size = new System.Drawing.Size(80, 22);
			this.installButton.TabIndex = 103;
			this.installButton.Text = "Install loader";
			this.installButton.UseVisualStyleBackColor = true;
			this.installButton.Click += new System.EventHandler(this.installButton_Click);
			// 
			// tabControl1
			// 
			this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tabControl1.Controls.Add(this.tabPage1);
			this.tabControl1.Controls.Add(this.tabPage2);
			this.tabControl1.Controls.Add(this.tabPage3);
			this.tabControl1.Controls.Add(this.tabPage4);
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Margin = new System.Windows.Forms.Padding(0, 0, 0, 3);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(386, 364);
			this.tabControl1.TabIndex = 0;
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.configureModButton);
			this.tabPage1.Controls.Add(this.modBottomButton);
			this.tabPage1.Controls.Add(this.modTopButton);
			this.tabPage1.Controls.Add(this.buttonNewMod);
			this.tabPage1.Controls.Add(this.buttonRefreshModList);
			this.tabPage1.Controls.Add(this.modDescription);
			this.tabPage1.Controls.Add(this.modDownButton);
			this.tabPage1.Controls.Add(this.modUpButton);
			this.tabPage1.Controls.Add(this.modListView);
			this.tabPage1.Location = new System.Drawing.Point(4, 22);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage1.Size = new System.Drawing.Size(378, 338);
			this.tabPage1.TabIndex = 0;
			this.tabPage1.Text = "Mods";
			this.tabPage1.UseVisualStyleBackColor = true;
			// 
			// configureModButton
			// 
			this.configureModButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.configureModButton.Enabled = false;
			this.configureModButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.configureModButton.Location = new System.Drawing.Point(87, 223);
			this.configureModButton.Name = "configureModButton";
			this.configureModButton.Size = new System.Drawing.Size(75, 23);
			this.configureModButton.TabIndex = 18;
			this.configureModButton.Text = "Configure...";
			this.configureModButton.UseVisualStyleBackColor = true;
			this.configureModButton.Click += new System.EventHandler(this.configureModButton_Click);
			// 
			// modBottomButton
			// 
			this.modBottomButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modBottomButton.AutoSize = true;
			this.modBottomButton.Enabled = false;
			this.modBottomButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modBottomButton.Location = new System.Drawing.Point(344, 90);
			this.modBottomButton.Name = "modBottomButton";
			this.modBottomButton.Size = new System.Drawing.Size(28, 22);
			this.modBottomButton.TabIndex = 17;
			this.modBottomButton.Text = "⤓";
			this.modBottomButton.UseVisualStyleBackColor = true;
			this.modBottomButton.Click += new System.EventHandler(this.modBottomButton_Click);
			// 
			// modTopButton
			// 
			this.modTopButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modTopButton.AutoSize = true;
			this.modTopButton.Enabled = false;
			this.modTopButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modTopButton.Location = new System.Drawing.Point(344, 6);
			this.modTopButton.Name = "modTopButton";
			this.modTopButton.Size = new System.Drawing.Size(28, 22);
			this.modTopButton.TabIndex = 16;
			this.modTopButton.Text = "⤒";
			this.modTopButton.UseVisualStyleBackColor = true;
			this.modTopButton.Click += new System.EventHandler(this.modTopButton_Click);
			// 
			// buttonNewMod
			// 
			this.buttonNewMod.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonNewMod.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.buttonNewMod.Location = new System.Drawing.Point(268, 223);
			this.buttonNewMod.Name = "buttonNewMod";
			this.buttonNewMod.Size = new System.Drawing.Size(75, 23);
			this.buttonNewMod.TabIndex = 14;
			this.buttonNewMod.Text = "&New...";
			this.buttonNewMod.UseVisualStyleBackColor = true;
			this.buttonNewMod.Click += new System.EventHandler(this.buttonNewMod_Click);
			// 
			// buttonRefreshModList
			// 
			this.buttonRefreshModList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.buttonRefreshModList.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.buttonRefreshModList.Location = new System.Drawing.Point(6, 223);
			this.buttonRefreshModList.Name = "buttonRefreshModList";
			this.buttonRefreshModList.Size = new System.Drawing.Size(75, 23);
			this.buttonRefreshModList.TabIndex = 13;
			this.buttonRefreshModList.Text = "&Refresh";
			this.buttonRefreshModList.UseVisualStyleBackColor = true;
			this.buttonRefreshModList.Click += new System.EventHandler(this.buttonRefreshModList_Click);
			// 
			// modDescription
			// 
			this.modDescription.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.modDescription.Location = new System.Drawing.Point(6, 252);
			this.modDescription.Name = "modDescription";
			this.modDescription.Size = new System.Drawing.Size(366, 36);
			this.modDescription.TabIndex = 15;
			this.modDescription.Text = "Description: No mod selected.";
			// 
			// modDownButton
			// 
			this.modDownButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modDownButton.AutoSize = true;
			this.modDownButton.Enabled = false;
			this.modDownButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modDownButton.Location = new System.Drawing.Point(344, 62);
			this.modDownButton.Name = "modDownButton";
			this.modDownButton.Size = new System.Drawing.Size(28, 22);
			this.modDownButton.TabIndex = 12;
			this.modDownButton.Text = "↓";
			this.modDownButton.UseVisualStyleBackColor = true;
			this.modDownButton.Click += new System.EventHandler(this.modDownButton_Click);
			// 
			// modUpButton
			// 
			this.modUpButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.modUpButton.AutoSize = true;
			this.modUpButton.Enabled = false;
			this.modUpButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.modUpButton.Location = new System.Drawing.Point(344, 34);
			this.modUpButton.Name = "modUpButton";
			this.modUpButton.Size = new System.Drawing.Size(28, 22);
			this.modUpButton.TabIndex = 11;
			this.modUpButton.Text = "↑";
			this.modUpButton.UseVisualStyleBackColor = true;
			this.modUpButton.Click += new System.EventHandler(this.modUpButton_Click);
			// 
			// modListView
			// 
			this.modListView.AllowDrop = true;
			this.modListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.modListView.CheckBoxes = true;
			this.modListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
			this.modListView.FullRowSelect = true;
			this.modListView.HideSelection = false;
			this.modListView.Location = new System.Drawing.Point(6, 6);
			this.modListView.Name = "modListView";
			this.modListView.Size = new System.Drawing.Size(337, 211);
			this.modListView.TabIndex = 10;
			this.modListView.UseCompatibleStateImageBehavior = false;
			this.modListView.View = System.Windows.Forms.View.Details;
			this.modListView.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.modListView_ItemCheck);
			this.modListView.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.modListView_ItemDrag);
			this.modListView.SelectedIndexChanged += new System.EventHandler(this.modListView_SelectedIndexChanged);
			this.modListView.DragDrop += new System.Windows.Forms.DragEventHandler(this.modListView_DragDrop);
			this.modListView.DragEnter += new System.Windows.Forms.DragEventHandler(this.modListView_DragEnter);
			this.modListView.DragOver += new System.Windows.Forms.DragEventHandler(this.modListView_DragOver);
			this.modListView.MouseClick += new System.Windows.Forms.MouseEventHandler(this.modListView_MouseClick);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Name";
			this.columnHeader1.Width = 154;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Author";
			this.columnHeader2.Width = 113;
			// 
			// columnHeader3
			// 
			this.columnHeader3.Text = "Version";
			// 
			// tabPage2
			// 
			this.tabPage2.Controls.Add(this.codesCheckedListBox);
			this.tabPage2.Location = new System.Drawing.Point(4, 22);
			this.tabPage2.Name = "tabPage2";
			this.tabPage2.Size = new System.Drawing.Size(378, 338);
			this.tabPage2.TabIndex = 1;
			this.tabPage2.Text = "Codes";
			this.tabPage2.UseVisualStyleBackColor = true;
			// 
			// codesCheckedListBox
			// 
			this.codesCheckedListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.codesCheckedListBox.FormattingEnabled = true;
			this.codesCheckedListBox.Location = new System.Drawing.Point(0, 0);
			this.codesCheckedListBox.Name = "codesCheckedListBox";
			this.codesCheckedListBox.Size = new System.Drawing.Size(378, 338);
			this.codesCheckedListBox.TabIndex = 0;
			this.codesCheckedListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.codesCheckedListBox_ItemCheck);
			// 
			// tabPage3
			// 
			this.tabPage3.Controls.Add(this.groupBox3);
			this.tabPage3.Location = new System.Drawing.Point(4, 22);
			this.tabPage3.Name = "tabPage3";
			this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage3.Size = new System.Drawing.Size(378, 338);
			this.tabPage3.TabIndex = 4;
			this.tabPage3.Text = "Graphics";
			this.tabPage3.UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox3.Controls.Add(this.comboResolutionPreset);
			this.groupBox3.Controls.Add(this.windowedCheckBox);
			this.groupBox3.Controls.Add(label5);
			this.groupBox3.Controls.Add(this.maintainWindowAspectRatioCheckBox);
			this.groupBox3.Controls.Add(this.windowWidth);
			this.groupBox3.Controls.Add(label2);
			this.groupBox3.Controls.Add(this.windowHeight);
			this.groupBox3.Controls.Add(this.customWindowSizeCheckBox);
			this.groupBox3.Controls.Add(this.stretchFullscreenCheckBox);
			this.groupBox3.Controls.Add(this.forceAspectRatioCheckBox);
			this.groupBox3.Controls.Add(this.horizontalResolution);
			this.groupBox3.Controls.Add(this.windowedFullscreenCheckBox);
			this.groupBox3.Controls.Add(label1);
			this.groupBox3.Controls.Add(this.verticalResolution);
			this.groupBox3.Location = new System.Drawing.Point(6, 6);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(366, 142);
			this.groupBox3.TabIndex = 1;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Display";
			// 
			// comboResolutionPreset
			// 
			this.comboResolutionPreset.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboResolutionPreset.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.comboResolutionPreset.FormattingEnabled = true;
			this.comboResolutionPreset.Items.AddRange(new object[] {
            "640x480",
            "800x600",
            "1024x768",
            "1152x864",
            "1280x1024",
            "Native",
            "1/2x Native",
            "2x Native",
            "720p",
            "1080p",
            "4K"});
			this.comboResolutionPreset.Location = new System.Drawing.Point(226, 41);
			this.comboResolutionPreset.Name = "comboResolutionPreset";
			this.comboResolutionPreset.Size = new System.Drawing.Size(121, 21);
			this.comboResolutionPreset.TabIndex = 18;
			this.toolTip1.SetToolTip(this.comboResolutionPreset, "Allows you to select pre-set values for the resolution.");
			this.comboResolutionPreset.SelectedIndexChanged += new System.EventHandler(this.comboResolutionPreset_SelectedIndexChanged);
			// 
			// windowedCheckBox
			// 
			this.windowedCheckBox.AutoSize = true;
			this.windowedCheckBox.Location = new System.Drawing.Point(6, 19);
			this.windowedCheckBox.Name = "windowedCheckBox";
			this.windowedCheckBox.Size = new System.Drawing.Size(77, 17);
			this.windowedCheckBox.TabIndex = 0;
			this.windowedCheckBox.Text = "Windowed";
			this.windowedCheckBox.UseVisualStyleBackColor = true;
			// 
			// maintainWindowAspectRatioCheckBox
			// 
			this.maintainWindowAspectRatioCheckBox.AutoSize = true;
			this.maintainWindowAspectRatioCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.maintainWindowAspectRatioCheckBox.Location = new System.Drawing.Point(6, 113);
			this.maintainWindowAspectRatioCheckBox.Name = "maintainWindowAspectRatioCheckBox";
			this.maintainWindowAspectRatioCheckBox.Size = new System.Drawing.Size(136, 18);
			this.maintainWindowAspectRatioCheckBox.TabIndex = 15;
			this.maintainWindowAspectRatioCheckBox.Text = "Maintain Aspect Ratio";
			this.toolTip1.SetToolTip(this.maintainWindowAspectRatioCheckBox, "Forces the window\'s aspect ratio to match the current custom resolution\'s.");
			this.maintainWindowAspectRatioCheckBox.UseVisualStyleBackColor = true;
			this.maintainWindowAspectRatioCheckBox.CheckedChanged += new System.EventHandler(this.maintainWindowAspectRatioCheckBox_CheckedChanged);
			// 
			// windowWidth
			// 
			this.windowWidth.Location = new System.Drawing.Point(151, 87);
			this.windowWidth.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
			this.windowWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.windowWidth.Name = "windowWidth";
			this.windowWidth.Size = new System.Drawing.Size(62, 20);
			this.windowWidth.TabIndex = 12;
			this.windowWidth.Value = new decimal(new int[] {
            640,
            0,
            0,
            0});
			// 
			// windowHeight
			// 
			this.windowHeight.Location = new System.Drawing.Point(237, 87);
			this.windowHeight.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
			this.windowHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.windowHeight.Name = "windowHeight";
			this.windowHeight.Size = new System.Drawing.Size(62, 20);
			this.windowHeight.TabIndex = 14;
			this.windowHeight.Value = new decimal(new int[] {
            480,
            0,
            0,
            0});
			this.windowHeight.ValueChanged += new System.EventHandler(this.windowHeight_ValueChanged);
			// 
			// customWindowSizeCheckBox
			// 
			this.customWindowSizeCheckBox.AutoSize = true;
			this.customWindowSizeCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.customWindowSizeCheckBox.Location = new System.Drawing.Point(6, 88);
			this.customWindowSizeCheckBox.Name = "customWindowSizeCheckBox";
			this.customWindowSizeCheckBox.Size = new System.Drawing.Size(135, 18);
			this.customWindowSizeCheckBox.TabIndex = 11;
			this.customWindowSizeCheckBox.Text = "Custom Window Size:";
			this.toolTip1.SetToolTip(this.customWindowSizeCheckBox, "Allows you to specify a fixed size for the window in windowed mode.");
			this.customWindowSizeCheckBox.UseVisualStyleBackColor = true;
			this.customWindowSizeCheckBox.CheckedChanged += new System.EventHandler(this.customWindowSizeCheckBox_CheckedChanged);
			// 
			// stretchFullscreenCheckBox
			// 
			this.stretchFullscreenCheckBox.AutoSize = true;
			this.stretchFullscreenCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.stretchFullscreenCheckBox.Location = new System.Drawing.Point(229, 18);
			this.stretchFullscreenCheckBox.Name = "stretchFullscreenCheckBox";
			this.stretchFullscreenCheckBox.Size = new System.Drawing.Size(108, 18);
			this.stretchFullscreenCheckBox.TabIndex = 3;
			this.stretchFullscreenCheckBox.Text = "Scale to Screen";
			this.toolTip1.SetToolTip(this.stretchFullscreenCheckBox, "Coupled with Windowed Fullscreen, you can downsample the game from resolutions hi" +
        "gher than your screen supports.");
			this.stretchFullscreenCheckBox.UseVisualStyleBackColor = true;
			// 
			// forceAspectRatioCheckBox
			// 
			this.forceAspectRatioCheckBox.AutoSize = true;
			this.forceAspectRatioCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.forceAspectRatioCheckBox.Location = new System.Drawing.Point(6, 65);
			this.forceAspectRatioCheckBox.Name = "forceAspectRatioCheckBox";
			this.forceAspectRatioCheckBox.Size = new System.Drawing.Size(141, 18);
			this.forceAspectRatioCheckBox.TabIndex = 10;
			this.forceAspectRatioCheckBox.Text = "Force 4:3 Aspect Ratio";
			this.forceAspectRatioCheckBox.UseVisualStyleBackColor = true;
			this.forceAspectRatioCheckBox.CheckedChanged += new System.EventHandler(this.forceAspectRatioCheckBox_CheckedChanged);
			// 
			// horizontalResolution
			// 
			this.horizontalResolution.Location = new System.Drawing.Point(72, 42);
			this.horizontalResolution.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
			this.horizontalResolution.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.horizontalResolution.Name = "horizontalResolution";
			this.horizontalResolution.Size = new System.Drawing.Size(62, 20);
			this.horizontalResolution.TabIndex = 6;
			this.horizontalResolution.Value = new decimal(new int[] {
            640,
            0,
            0,
            0});
			this.horizontalResolution.ValueChanged += new System.EventHandler(this.horizontalResolution_ValueChanged);
			// 
			// windowedFullscreenCheckBox
			// 
			this.windowedFullscreenCheckBox.AutoSize = true;
			this.windowedFullscreenCheckBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.windowedFullscreenCheckBox.Location = new System.Drawing.Point(89, 18);
			this.windowedFullscreenCheckBox.Name = "windowedFullscreenCheckBox";
			this.windowedFullscreenCheckBox.Size = new System.Drawing.Size(134, 18);
			this.windowedFullscreenCheckBox.TabIndex = 2;
			this.windowedFullscreenCheckBox.Text = "Windowed Fullscreen";
			this.toolTip1.SetToolTip(this.windowedFullscreenCheckBox, "Enables borderless fullscreen mode.\r\nYou have to enable fullscreen in the config " +
        "editor for it to work.");
			this.windowedFullscreenCheckBox.UseVisualStyleBackColor = true;
			// 
			// verticalResolution
			// 
			this.verticalResolution.Location = new System.Drawing.Point(158, 42);
			this.verticalResolution.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
			this.verticalResolution.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.verticalResolution.Name = "verticalResolution";
			this.verticalResolution.Size = new System.Drawing.Size(62, 20);
			this.verticalResolution.TabIndex = 8;
			this.verticalResolution.Value = new decimal(new int[] {
            480,
            0,
            0,
            0});
			this.verticalResolution.ValueChanged += new System.EventHandler(this.verticalResolution_ValueChanged);
			// 
			// tabPage4
			// 
			this.tabPage4.Controls.Add(this.installURLHandlerButton);
			this.tabPage4.Controls.Add(this.groupBox4);
			this.tabPage4.Controls.Add(this.groupBox1);
			this.tabPage4.Location = new System.Drawing.Point(4, 22);
			this.tabPage4.Name = "tabPage4";
			this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage4.Size = new System.Drawing.Size(378, 338);
			this.tabPage4.TabIndex = 3;
			this.tabPage4.Text = "Options";
			this.tabPage4.UseVisualStyleBackColor = true;
			// 
			// installURLHandlerButton
			// 
			this.installURLHandlerButton.AutoSize = true;
			this.installURLHandlerButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.installURLHandlerButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.installURLHandlerButton.Location = new System.Drawing.Point(6, 157);
			this.installURLHandlerButton.Name = "installURLHandlerButton";
			this.installURLHandlerButton.Size = new System.Drawing.Size(113, 22);
			this.installURLHandlerButton.TabIndex = 4;
			this.installURLHandlerButton.Text = "Install URL Handler";
			this.installURLHandlerButton.UseVisualStyleBackColor = true;
			this.installURLHandlerButton.Click += new System.EventHandler(this.installURLHandlerButton_Click);
			// 
			// groupBox4
			// 
			this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox4.Controls.Add(this.buttonCheckForUpdates);
			this.groupBox4.Controls.Add(this.label4);
			this.groupBox4.Controls.Add(this.checkUpdateModsStartup);
			this.groupBox4.Controls.Add(this.numericUpdateFrequency);
			this.groupBox4.Controls.Add(this.comboUpdateFrequency);
			this.groupBox4.Controls.Add(this.checkUpdateStartup);
			this.groupBox4.Location = new System.Drawing.Point(3, 61);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(366, 90);
			this.groupBox4.TabIndex = 3;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Updates";
			// 
			// buttonCheckForUpdates
			// 
			this.buttonCheckForUpdates.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.buttonCheckForUpdates.Location = new System.Drawing.Point(259, 55);
			this.buttonCheckForUpdates.Name = "buttonCheckForUpdates";
			this.buttonCheckForUpdates.Size = new System.Drawing.Size(75, 23);
			this.buttonCheckForUpdates.TabIndex = 5;
			this.buttonCheckForUpdates.Text = "Check Now";
			this.buttonCheckForUpdates.UseVisualStyleBackColor = true;
			this.buttonCheckForUpdates.Click += new System.EventHandler(this.buttonCheckForUpdates_Click);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(6, 40);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(60, 13);
			this.label4.TabIndex = 2;
			this.label4.Text = "Frequency:";
			// 
			// checkUpdateModsStartup
			// 
			this.checkUpdateModsStartup.AutoSize = true;
			this.checkUpdateModsStartup.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.checkUpdateModsStartup.Location = new System.Drawing.Point(133, 19);
			this.checkUpdateModsStartup.Name = "checkUpdateModsStartup";
			this.checkUpdateModsStartup.Size = new System.Drawing.Size(141, 18);
			this.checkUpdateModsStartup.TabIndex = 1;
			this.checkUpdateModsStartup.Text = "Check mods on startup";
			this.checkUpdateModsStartup.UseVisualStyleBackColor = true;
			// 
			// numericUpdateFrequency
			// 
			this.numericUpdateFrequency.Location = new System.Drawing.Point(133, 57);
			this.numericUpdateFrequency.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this.numericUpdateFrequency.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.numericUpdateFrequency.Name = "numericUpdateFrequency";
			this.numericUpdateFrequency.Size = new System.Drawing.Size(120, 20);
			this.numericUpdateFrequency.TabIndex = 4;
			this.numericUpdateFrequency.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
			// 
			// comboUpdateFrequency
			// 
			this.comboUpdateFrequency.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboUpdateFrequency.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.comboUpdateFrequency.FormattingEnabled = true;
			this.comboUpdateFrequency.Items.AddRange(new object[] {
            "Always",
            "Hours",
            "Days",
            "Weeks"});
			this.comboUpdateFrequency.Location = new System.Drawing.Point(6, 56);
			this.comboUpdateFrequency.Name = "comboUpdateFrequency";
			this.comboUpdateFrequency.Size = new System.Drawing.Size(121, 21);
			this.comboUpdateFrequency.TabIndex = 3;
			this.comboUpdateFrequency.SelectedIndexChanged += new System.EventHandler(this.comboUpdateFrequency_SelectedIndexChanged);
			// 
			// checkUpdateStartup
			// 
			this.checkUpdateStartup.AutoSize = true;
			this.checkUpdateStartup.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.checkUpdateStartup.Location = new System.Drawing.Point(6, 19);
			this.checkUpdateStartup.Name = "checkUpdateStartup";
			this.checkUpdateStartup.Size = new System.Drawing.Size(113, 18);
			this.checkUpdateStartup.TabIndex = 0;
			this.checkUpdateStartup.Text = "Check on startup";
			this.checkUpdateStartup.UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.debugFileCheckBox);
			this.groupBox1.Controls.Add(this.debugConsoleCheckBox);
			this.groupBox1.Location = new System.Drawing.Point(6, 6);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 3, 3, 0);
			this.groupBox1.Size = new System.Drawing.Size(366, 49);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Debug Messages";
			// 
			// debugFileCheckBox
			// 
			this.debugFileCheckBox.AutoSize = true;
			this.debugFileCheckBox.Location = new System.Drawing.Point(76, 19);
			this.debugFileCheckBox.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
			this.debugFileCheckBox.Name = "debugFileCheckBox";
			this.debugFileCheckBox.Size = new System.Drawing.Size(42, 17);
			this.debugFileCheckBox.TabIndex = 1;
			this.debugFileCheckBox.Text = "&File";
			this.debugFileCheckBox.UseVisualStyleBackColor = true;
			// 
			// debugConsoleCheckBox
			// 
			this.debugConsoleCheckBox.AutoSize = true;
			this.debugConsoleCheckBox.Location = new System.Drawing.Point(6, 19);
			this.debugConsoleCheckBox.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
			this.debugConsoleCheckBox.Name = "debugConsoleCheckBox";
			this.debugConsoleCheckBox.Size = new System.Drawing.Size(64, 17);
			this.debugConsoleCheckBox.TabIndex = 0;
			this.debugConsoleCheckBox.Text = "&Console";
			this.debugConsoleCheckBox.UseVisualStyleBackColor = true;
			// 
			// modContextMenu
			// 
			this.modContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFolderToolStripMenuItem,
            this.toolStripMenuItem1,
            this.checkForUpdatesToolStripMenuItem,
            this.verifyToolStripMenuItem,
            this.forceUpdateToolStripMenuItem,
            this.uninstallToolStripMenuItem,
            this.toolStripMenuItem3,
            this.developerToolStripMenuItem});
			this.modContextMenu.Name = "modContextMenu";
			this.modContextMenu.Size = new System.Drawing.Size(171, 148);
			// 
			// openFolderToolStripMenuItem
			// 
			this.openFolderToolStripMenuItem.Name = "openFolderToolStripMenuItem";
			this.openFolderToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.openFolderToolStripMenuItem.Text = "Open folder";
			this.openFolderToolStripMenuItem.Click += new System.EventHandler(this.openFolderToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(167, 6);
			// 
			// checkForUpdatesToolStripMenuItem
			// 
			this.checkForUpdatesToolStripMenuItem.Name = "checkForUpdatesToolStripMenuItem";
			this.checkForUpdatesToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.checkForUpdatesToolStripMenuItem.Text = "Check for updates";
			this.checkForUpdatesToolStripMenuItem.Click += new System.EventHandler(this.checkForUpdatesToolStripMenuItem_Click);
			// 
			// verifyToolStripMenuItem
			// 
			this.verifyToolStripMenuItem.Name = "verifyToolStripMenuItem";
			this.verifyToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.verifyToolStripMenuItem.Text = "Verify integrity";
			this.verifyToolStripMenuItem.Click += new System.EventHandler(this.verifyToolStripMenuItem_Click);
			// 
			// forceUpdateToolStripMenuItem
			// 
			this.forceUpdateToolStripMenuItem.Name = "forceUpdateToolStripMenuItem";
			this.forceUpdateToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.forceUpdateToolStripMenuItem.Text = "Force update";
			this.forceUpdateToolStripMenuItem.Click += new System.EventHandler(this.forceUpdateToolStripMenuItem_Click);
			// 
			// uninstallToolStripMenuItem
			// 
			this.uninstallToolStripMenuItem.Name = "uninstallToolStripMenuItem";
			this.uninstallToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.uninstallToolStripMenuItem.Text = "Uninstall";
			this.uninstallToolStripMenuItem.Click += new System.EventHandler(this.uninstallToolStripMenuItem_Click);
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(167, 6);
			// 
			// developerToolStripMenuItem
			// 
			this.developerToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generateManifestToolStripMenuItem});
			this.developerToolStripMenuItem.Name = "developerToolStripMenuItem";
			this.developerToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.developerToolStripMenuItem.Text = "Developer";
			// 
			// generateManifestToolStripMenuItem
			// 
			this.generateManifestToolStripMenuItem.Name = "generateManifestToolStripMenuItem";
			this.generateManifestToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.generateManifestToolStripMenuItem.Text = "Generate manifest";
			this.generateManifestToolStripMenuItem.Click += new System.EventHandler(this.generateManifestToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(384, 409);
			this.Controls.Add(this.tabControl1);
			this.Controls.Add(this.installButton);
			this.Controls.Add(this.saveAndPlayButton);
			this.Controls.Add(this.saveButton);
			this.MinimumSize = new System.Drawing.Size(400, 400);
			this.Name = "MainForm";
			this.Padding = new System.Windows.Forms.Padding(0, 0, 0, 3);
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
			this.Text = "Sonic R Mod Manager";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.Shown += new System.EventHandler(this.MainForm_Shown);
			this.tabControl1.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.tabPage1.PerformLayout();
			this.tabPage2.ResumeLayout(false);
			this.tabPage3.ResumeLayout(false);
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.windowWidth)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.windowHeight)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.horizontalResolution)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.verticalResolution)).EndInit();
			this.tabPage4.ResumeLayout(false);
			this.tabPage4.PerformLayout();
			this.groupBox4.ResumeLayout(false);
			this.groupBox4.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpdateFrequency)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.modContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button saveAndPlayButton;
		private System.Windows.Forms.Button installButton;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private System.Windows.Forms.CheckedListBox codesCheckedListBox;
		private System.Windows.Forms.ToolTip toolTip1;
		private System.Windows.Forms.TabPage tabPage4;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox debugFileCheckBox;
		private System.Windows.Forms.CheckBox debugConsoleCheckBox;
		private System.Windows.Forms.TabPage tabPage3;
		private System.Windows.Forms.CheckBox windowedCheckBox;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.ComboBox comboResolutionPreset;
		private System.Windows.Forms.CheckBox maintainWindowAspectRatioCheckBox;
		private System.Windows.Forms.NumericUpDown windowWidth;
		private System.Windows.Forms.NumericUpDown windowHeight;
		private System.Windows.Forms.CheckBox customWindowSizeCheckBox;
		private System.Windows.Forms.CheckBox stretchFullscreenCheckBox;
		private System.Windows.Forms.CheckBox forceAspectRatioCheckBox;
		private System.Windows.Forms.NumericUpDown horizontalResolution;
		private System.Windows.Forms.CheckBox windowedFullscreenCheckBox;
		private System.Windows.Forms.NumericUpDown verticalResolution;
		private System.Windows.Forms.Button configureModButton;
		private System.Windows.Forms.Button modBottomButton;
		private System.Windows.Forms.Button modTopButton;
		private System.Windows.Forms.Button buttonNewMod;
		private System.Windows.Forms.Button buttonRefreshModList;
		private System.Windows.Forms.Label modDescription;
		private System.Windows.Forms.Button modDownButton;
		private System.Windows.Forms.Button modUpButton;
		private System.Windows.Forms.ListView modListView;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader3;
		private System.Windows.Forms.ContextMenuStrip modContextMenu;
		private System.Windows.Forms.ToolStripMenuItem openFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem checkForUpdatesToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem verifyToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem forceUpdateToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem uninstallToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem developerToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem generateManifestToolStripMenuItem;
		private System.Windows.Forms.Button installURLHandlerButton;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Button buttonCheckForUpdates;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.CheckBox checkUpdateModsStartup;
		private System.Windows.Forms.NumericUpDown numericUpdateFrequency;
		private System.Windows.Forms.ComboBox comboUpdateFrequency;
		private System.Windows.Forms.CheckBox checkUpdateStartup;
	}
}