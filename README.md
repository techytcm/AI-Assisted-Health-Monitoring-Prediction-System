<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AI-Assisted Health Monitoring & Prediction System</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            padding: 20px;
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            border-radius: 15px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.2);
            overflow: hidden;
        }

        header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 40px;
            text-align: center;
        }

        header h1 {
            font-size: 2.5em;
            margin-bottom: 10px;
        }

        header p {
            font-size: 1.2em;
            opacity: 0.9;
        }

        .content {
            padding: 40px;
        }

        h2 {
            color: #667eea;
            margin-top: 30px;
            margin-bottom: 15px;
            font-size: 2em;
            border-bottom: 3px solid #667eea;
            padding-bottom: 10px;
        }

        h3 {
            color: #764ba2;
            margin-top: 20px;
            margin-bottom: 10px;
            font-size: 1.5em;
        }

        .feature-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 20px;
            margin: 20px 0;
        }

        .feature-card {
            background: #f8f9fa;
            padding: 25px;
            border-radius: 10px;
            border-left: 4px solid #667eea;
            transition: transform 0.3s, box-shadow 0.3s;
        }

        .feature-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 5px 20px rgba(0,0,0,0.1);
        }

        .feature-card h3 {
            margin-top: 0;
            color: #667eea;
        }

        ul {
            margin-left: 20px;
            margin-bottom: 15px;
        }

        li {
            margin-bottom: 8px;
        }

        .highlight-box {
            background: #e7f3ff;
            border-left: 4px solid #2196F3;
            padding: 20px;
            margin: 20px 0;
            border-radius: 5px;
        }

        .warning-box {
            background: #fff3cd;
            border-left: 4px solid #ffc107;
            padding: 20px;
            margin: 20px 0;
            border-radius: 5px;
        }

        .success-box {
            background: #d4edda;
            border-left: 4px solid #28a745;
            padding: 20px;
            margin: 20px 0;
            border-radius: 5px;
        }

        code {
            background: #f4f4f4;
            padding: 2px 6px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
            color: #e83e8c;
        }

        pre {
            background: #2d2d2d;
            color: #f8f8f2;
            padding: 20px;
            border-radius: 5px;
            overflow-x: auto;
            margin: 15px 0;
        }

        pre code {
            background: none;
            color: #f8f8f2;
        }

        .badge {
            display: inline-block;
            padding: 5px 12px;
            background: #667eea;
            color: white;
            border-radius: 20px;
            font-size: 0.9em;
            margin: 5px 5px 5px 0;
        }

        .tech-spec {
            display: grid;
            grid-template-columns: 200px 1fr;
            gap: 10px;
            margin: 10px 0;
        }

        .tech-spec strong {
            color: #667eea;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }

        table th, table td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }

        table th {
            background: #667eea;
            color: white;
        }

        table tr:hover {
            background: #f5f5f5;
        }

        .btn {
            display: inline-block;
            padding: 12px 30px;
            background: #667eea;
            color: white;
            text-decoration: none;
            border-radius: 5px;
            transition: background 0.3s;
            margin: 10px 10px 10px 0;
        }

        .btn:hover {
            background: #764ba2;
        }

        footer {
            background: #2d2d2d;
            color: white;
            text-align: center;
            padding: 30px;
        }

        .icon {
            font-size: 2em;
            margin-bottom: 10px;
        }

        @media (max-width: 768px) {
            header h1 {
                font-size: 1.8em;
            }

            .content {
                padding: 20px;
            }

            .feature-grid {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <div class="icon">🏥</div>
            <h1>AI-Assisted Health Monitoring & Prediction System</h1>
            <p>Real-time patient vital tracking with AI-powered risk assessment</p>
        </header>

        <div class="content">
            <section id="overview">
                <h2>📋 Overview</h2>
                <p>This system provides a complete healthcare management solution with role-based access control for administrators, doctors, and patients. It features intelligent risk prediction algorithms that analyze patient vitals and generate actionable health insights.</p>
            </section>

            <section id="features">
                <h2>✨ Key Features</h2>
                
                <div class="feature-grid">
                    <div class="feature-card">
                        <h3>🔐 Multi-Role Authentication</h3>
                        <ul>
                            <li><strong>Admin Panel:</strong> Full system control</li>
                            <li><strong>Doctor Portal:</strong> Patient management</li>
                            <li><strong>Patient Portal:</strong> Health records access</li>
                        </ul>
                    </div>

                    <div class="feature-card">
                        <h3>💉 Real-Time Vital Monitoring</h3>
                        <ul>
                            <li>Heart Rate (BPM)</li>
                            <li>Blood Pressure (Systolic/Diastolic)</li>
                            <li>Body Temperature (°F)</li>
                            <li>Blood Sugar Levels (mg/dL)</li>
                            <li>SpO2 (Oxygen Saturation %)</li>
                            <li>Respiration Rate</li>
                        </ul>
                    </div>

                    <div class="feature-card">
                        <h3>🤖 AI-Powered Risk Assessment</h3>
                        <ul>
                            <li>Automated risk score (0-100)</li>
                            <li>Three-tier classification</li>
                            <li>Intelligent vital analysis</li>
                            <li>Critical condition detection</li>
                        </ul>
                    </div>

                    <div class="feature-card">
                        <h3>📊 Health Analytics</h3>
                        <ul>
                            <li>Comprehensive reports</li>
                            <li>Historical trend analysis</li>
                            <li>Average vital statistics</li>
                            <li>Personalized recommendations</li>
                        </ul>
                    </div>
                </div>
            </section>

            <section id="technical">
                <h2>🛠️ Technical Specifications</h2>
                <div class="tech-spec">
                    <strong>Language:</strong>
                    <span>C Programming</span>
                </div>
                <div class="tech-spec">
                    <strong>Platform:</strong>
                    <span>Cross-platform (Windows/Linux/Unix)</span>
                </div>
                <div class="tech-spec">
                    <strong>Storage:</strong>
                    <span>Binary file-based database system</span>
                </div>
                <div class="tech-spec">
                    <strong>Architecture:</strong>
                    <span>Modular design with role-based modules</span>
                </div>

                <h3>Data Files</h3>
                <ul>
                    <li><code>doctors.dat</code> - Doctor records</li>
                    <li><code>patients.dat</code> - Patient records</li>
                    <li><code>health_records.dat</code> - Medical examination records</li>
                </ul>
            </section>

            <section id="getting-started">
                <h2>🚀 Getting Started</h2>
                
                <h3>Prerequisites</h3>
                <ul>
                    <li>GCC compiler (or any C compiler)</li>
                    <li>Terminal/Command Prompt with color support</li>
                </ul>

                <h3>Compilation</h3>
                <p><strong>Windows:</strong></p>
                <pre><code>gcc -o health_system main.c</code></pre>

                <p><strong>Linux/Unix:</strong></p>
                <pre><code>gcc -o health_system main.c
./health_system</code></pre>

                <div class="warning-box">
                    <h3>⚠️ Default Admin Credentials</h3>
                    <p><strong>Username:</strong> <code>tcm9798</code></p>
                    <p><strong>Password:</strong> <code>tcm@4626</code></p>
                </div>
            </section>

            <section id="usage">
                <h2>📖 Usage Guide</h2>
                
                <div class="feature-grid">
                    <div class="feature-card">
                        <h3>Admin Functions</h3>
                        <ol>
                            <li>Add/Remove doctors and patients</li>
                            <li>View all system users</li>
                            <li>Access all medical records</li>
                            <li>System-wide monitoring</li>
                        </ol>
                    </div>

                    <div class="feature-card">
                        <h3>Doctor Functions</h3>
                        <ol>
                            <li>Record patient vital signs</li>
                            <li>View patient medical history</li>
                            <li>Generate health reports</li>
                            <li>Monitor assigned patients</li>
                            <li>Real-time risk assessment</li>
                        </ol>
                    </div>

                    <div class="feature-card">
                        <h3>Patient Functions</h3>
                        <ol>
                            <li>View personal profile</li>
                            <li>Access health reports</li>
                            <li>View health analytics</li>
                            <li>Track risk levels over time</li>
                        </ol>
                    </div>
                </div>
            </section>

            <section id="use-cases">
                <h2>🎯 Use Cases</h2>
                <div class="feature-grid">
                    <div class="feature-card">
                        <strong>🏥 Clinics</strong>
                        <p>Small to medium healthcare facilities</p>
                    </div>
                    <div class="feature-card">
                        <strong>⛺ Health Camps</strong>
                        <p>Temporary health screening events</p>
                    </div>
                    <div class="feature-card">
                        <strong>🏠 Home Healthcare</strong>
                        <p>Remote patient monitoring</p>
                    </div>
                    <div class="feature-card">
                        <strong>🎓 Educational</strong>
                        <p>Medical training and demonstrations</p>
                    </div>
                    <div class="feature-card">
                        <strong>🔬 Research</strong>
                        <p>Health data collection and analysis</p>
                    </div>
                </div>
            </section>

            <section id="algorithm">
                <h2>🔮 AI Risk Prediction Algorithm</h2>
                <p>The system uses a sophisticated scoring algorithm that considers:</p>
                <ul>
                    <li>Individual vital sign thresholds</li>
                    <li>Combined risk factors</li>
                    <li>Historical health patterns</li>
                    <li>Critical condition indicators</li>
                </ul>

                <h3>Risk Scoring Breakdown</h3>
                <table>
                    <thead>
                        <tr>
                            <th>Score Range</th>
                            <th>Risk Level</th>
                            <th>Description</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>0-29</td>
                            <td><span class="badge" style="background: #28a745;">LOW</span></td>
                            <td>Normal health status</td>
                        </tr>
                        <tr>
                            <td>30-59</td>
                            <td><span class="badge" style="background: #ffc107;">MEDIUM</span></td>
                            <td>Requires monitoring</td>
                        </tr>
                        <tr>
                            <td>60-100</td>
                            <td><span class="badge" style="background: #dc3545;">HIGH</span></td>
                            <td>Immediate attention needed</td>
                        </tr>
                    </tbody>
                </table>
            </section>

            <section id="security">
                <h2>🔒 Security Features</h2>
                <div class="success-box">
                    <ul>
                        <li>✅ Role-based access control</li>
                        <li>✅ Soft-delete mechanism for data integrity</li>
                        <li>✅ Input validation and sanitization</li>
                        <li>✅ Secure file handling</li>
                    </ul>
                </div>
            </section>

            <section id="highlights">
                <h2>🌟 Highlights</h2>
                <div class="feature-grid">
                    <span class="badge">Zero external dependencies</span>
                    <span class="badge">Lightweight and fast</span>
                    <span class="badge">Cross-platform compatible</span>
                    <span class="badge">Easy to deploy</span>
                    <span class="badge">Comprehensive error handling</span>
                    <span class="badge">Professional UI/UX design</span>
                </div>
            </section>

            <section id="contributing">
                <h2>🤝 Contributing</h2>
                <p>Contributions are welcome! Areas for enhancement:</p>
                <ul>
                    <li>Database encryption</li>
                    <li>Network capabilities</li>
                    <li>Additional vital parameters</li>
                    <li>Machine learning integration</li>
                    <li>Mobile app interface</li>
                </ul>
            </section>

            <section id="developer">
                <h2>👨‍💻 Developer</h2>
                <div class="highlight-box">
                    <p><strong>Developed by:</strong> techytcm</p>
                    <p><strong>Version:</strong> 1.0</p>
                    <p><strong>Language:</strong> C Programming</p>
                </div>
            </section>

            <section id="license">
                <h2>📝 License</h2>
                <p>This project is open-source and available for educational and non-commercial use.</p>
            </section>

            <div style="text-align: center; margin: 40px 0;">
                <a href="#" class="btn">⭐ Star this Repository</a>
                <a href="#" class="btn">📥 Download</a>
                <a href="#" class="btn">📞 Get Support</a>
            </div>
        </div>

        <footer>
            <p>&copy; 2024 AI-Assisted Health Monitoring System | Developed by techytcm</p>
            <p>For issues, questions, or suggestions, please open an issue in the repository.</p>
        </footer>
    </div>
</body>
</html
